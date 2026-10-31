/*
 *  \brief SoS: Statistics on Strings, a simple client-server application
 *    that computes some statistics on strings
 *
 * \author (2022-2026) Artur Pereira <artur at ua.pt>
 * \author (2022-2026) Miguel Oliveira e Silva <mos at ua.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdint.h>
#include <ctype.h>
#include <new>
#include <pthread.h>

#include "sos.h"
#include "utils.h"
#include "dbc.h"
#include "hdp.h"

/** \brief Number of transaction buffers */
#define  NBUFFERS         5

/** \brief indexes for the fifos of free buffers and of pending requests */
enum { 
    FREE_BUFFER = 0, 
    PENDING_REQUEST = 1 
};

/* -------------------------------------------------------------------- */

/** \brief interaction buffer data type */
struct BUFFER 
{
    char req[MAX_STRING_LEN+1];         ///< The request recipient
    Response resp;                      ///< The response recipient
    bool thereIsResponse;               ///< condition stating the response is in place
    pthread_cond_t responseAvailable;   ///< condition variable to notify client the response is available
    pthread_mutex_t access;             ///< access mutex for this buffer
};

/* -------------------------------------------------------------------- */

/** \brief the fifo data type to store indexes of buffers */
struct Fifo
{
    uint32_t ii;               ///< point of insertion
    uint32_t ri;               ///< point of retrieval
    uint32_t cnt;              ///< number of items stored
    uint32_t tokens[NBUFFERS]; ///< storage memory
    pthread_mutex_t access;    ///< access mutex
    pthread_cond_t notFull;    ///< condition variable to wait for not fullness
    pthread_cond_t notEmpty;   ///< condition variable to wait for not emptiness
};

/* -------------------------------------------------------------------- */

/** \brief the data type representing all the shared area.
 *    Fifo 0 is used to manage tokens of free buffers.
 *    Fifo 1 is used to manage tokens of pending requests.
 */
struct SharedArea
{
    /* A fix number of transaction buffers */
    BUFFER pool[NBUFFERS];

    /* A fifo for tokens of free buffers and another for tokens with pending requests */
    Fifo fifo[2];
};

/** \brief pointer to shared area dynamically allocated */
SharedArea *sharedArea = NULL;

/* -------------------------------------------------------------------- */

static void mutex_unlock_handler(void *arg)
{
    pthread_mutex_t *mtx = (pthread_mutex_t *)arg;
    pthread_mutex_unlock(mtx);
}

/** \brief The fifo manipulation functions */

/* Insert a token into a fifo */
static void fifoIn(uint32_t semIndex, uint32_t token)
{
#if __DEBUG__
    fprintf(stderr, "%s(semIndex: %u, token: %u)\n", __func__, semIndex, token);
#endif

    /* check preconditions */
    require(semIndex == FREE_BUFFER or semIndex == PENDING_REQUEST, "semIndex is not valid");
    require(token < NBUFFERS, "Token is not valid");

    Fifo *f = &sharedArea->fifo[semIndex];

    NZ(pthread_mutex_lock(&f->access));
    pthread_cleanup_push(mutex_unlock_handler, &f->access);

    while (f->cnt == NBUFFERS)
    {
        NZ(pthread_cond_wait(&f->notFull, &f->access));
    }

    f->tokens[f->ii] = token;
    f->ii = (f->ii + 1) % NBUFFERS;
    f->cnt++;

    NZ(pthread_cond_broadcast(&f->notEmpty));

    pthread_cleanup_pop(1);
}

/* -------------------------------------------------------------------- */

/* Retrieve a token from a fifo  */
static uint32_t fifoOut(uint32_t semIndex)
{
#if __DEBUG__
    fprintf(stderr, "%s(semIndex: %u)\n", __func__, semIndex);
#endif

    /* check preconditions */
    require(semIndex == FREE_BUFFER or semIndex == PENDING_REQUEST, "semIndex is not valid");

    Fifo *f = &sharedArea->fifo[semIndex];
    uint32_t token;

    NZ(pthread_mutex_lock(&f->access));
    pthread_cleanup_push(mutex_unlock_handler, &f->access);

    while (f->cnt == 0)
    {
        NZ(pthread_cond_wait(&f->notEmpty, &f->access));
    }

    token = f->tokens[f->ri];
    f->ri = (f->ri + 1) % NBUFFERS;
    f->cnt--;

    NZ(pthread_cond_broadcast(&f->notFull));

    pthread_cleanup_pop(1);

    return token;
}


/* -------------------------------------------------------------------- */

/* Allocate and init the internal supporting data structure,
 *   including all necessary synchronization resources
 */
void init(void)
{
#if __DEBUG__
    fprintf(stderr, "%s()\n", __func__);
#endif

    require(sharedArea == NULL, "Shared area must not yet exist");

    sharedArea = new SharedArea;

    /* Initialize transaction buffers */
    for (uint32_t i = 0; i < NBUFFERS; i++)
    {
        sharedArea->pool[i].req[0] = '\0';
        sharedArea->pool[i].thereIsResponse = false;
        NZ(pthread_cond_init(&sharedArea->pool[i].responseAvailable, NULL));
        NZ(pthread_mutex_init(&sharedArea->pool[i].access, NULL));
    }

    /* Initialize fifos */
    for (uint32_t f = 0; f < 2; f++)
    {
        sharedArea->fifo[f].ii = 0;
        sharedArea->fifo[f].ri = 0;
        sharedArea->fifo[f].cnt = 0;
        NZ(pthread_mutex_init(&sharedArea->fifo[f].access, NULL));
        NZ(pthread_cond_init(&sharedArea->fifo[f].notFull, NULL));
        NZ(pthread_cond_init(&sharedArea->fifo[f].notEmpty, NULL));
    }

    /* Initially all buffers are free */
    for (uint32_t i = 0; i < NBUFFERS; i++)
    {
        fifoIn(FREE_BUFFER, i);
    }
}

/* -------------------------------------------------------------------- */

/* Free all allocated synchronization resources and data structures */
void destroy()
{
    require(sharedArea != NULL, "Shared area must be allocated");

    /* Destroy fifos */
    for (uint32_t f = 0; f < 2; f++)
    {
        NZ(pthread_cond_destroy(&sharedArea->fifo[f].notFull));
        NZ(pthread_cond_destroy(&sharedArea->fifo[f].notEmpty));
        NZ(pthread_mutex_destroy(&sharedArea->fifo[f].access));
    }

    /* Destroy transaction buffers */
    for (uint32_t i = 0; i < NBUFFERS; i++)
    {
        NZ(pthread_cond_destroy(&sharedArea->pool[i].responseAvailable));
        NZ(pthread_mutex_destroy(&sharedArea->pool[i].access));
    }

    delete sharedArea;
    sharedArea = NULL;
}

/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */

uint32_t getFreeBuffer()
{
#if __DEBUG__
    fprintf(stderr, "%s()\n", __func__);
#endif

    return fifoOut(FREE_BUFFER);
}

/* -------------------------------------------------------------------- */

void putRequestData(uint32_t token, const char *data)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u, ...)\n", __func__, token);
#endif

    require(token < NBUFFERS, "Token is not valid");
    require(data != NULL, "Data pointer can not be NULL");

    char *req = sharedArea->pool[token].req;
    strncpy(req, data, MAX_STRING_LEN);
    req[MAX_STRING_LEN] = '\0';
}

/* -------------------------------------------------------------------- */

void submitRequest(uint32_t token)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u)\n", __func__, token);
#endif

    require(token < NBUFFERS, "Token is not valid");

    NZ(pthread_mutex_lock(&sharedArea->pool[token].access));
    sharedArea->pool[token].thereIsResponse = false;
    NZ(pthread_mutex_unlock(&sharedArea->pool[token].access));

    fifoIn(PENDING_REQUEST, token);
}

/* -------------------------------------------------------------------- */

void waitForResponse(uint32_t token)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u)\n", __func__, token);
#endif

    require(token < NBUFFERS, "Token is not valid");

    BUFFER *b = &sharedArea->pool[token];

    NZ(pthread_mutex_lock(&b->access));
    pthread_cleanup_push(mutex_unlock_handler, &b->access);

    while (!b->thereIsResponse)
    {
        NZ(pthread_cond_wait(&b->responseAvailable, &b->access));
    }

    pthread_cleanup_pop(1);
}

/* -------------------------------------------------------------------- */

void getResponseData(uint32_t token, Response *resp)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u, ...)\n", __func__, token);
#endif

    require(token < NBUFFERS, "token is not valid");
    require(resp != NULL, "Resp pointer can not be NULL");

    *resp = sharedArea->pool[token].resp;
}

/* -------------------------------------------------------------------- */

void releaseBuffer(uint32_t token)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u)\n", __func__, token);
#endif

    require(token < NBUFFERS, "Token is not valid");

    fifoIn(FREE_BUFFER, token);
}

/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */

uint32_t getPendingRequest()
{
#if __DEBUG__
    fprintf(stderr, "%s()\n", __func__);
#endif

    return fifoOut(PENDING_REQUEST);
}

/* -------------------------------------------------------------------- */

void getRequestData(uint32_t token, char *data)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u, ...)\n", __func__, token);
#endif

    require(token < NBUFFERS, "Token is not valid");
    require(data != NULL, "Data pointer can not be NULL");

    char *req = sharedArea->pool[token].req;
    strncpy(data, req, MAX_STRING_LEN);
    data[MAX_STRING_LEN] = '\0';
}

/* -------------------------------------------------------------------- */

Response produceResponse(char *req)
{
#if __DEBUG__
    fprintf(stderr, "%s(req: %s)\n", __func__, req);
#endif

    Response resp = {0,0,0};
    for (uint32_t i = 0; req[i] != '\0'; i++)
    {
        resp.noChars++;
        if (isdigit(req[i])) resp.noDigits++;
        if (isalpha(req[i])) resp.noLetters++;
    }
    return resp;
}

/* -------------------------------------------------------------------- */

void putResponseData(uint32_t token, Response *resp)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u, ...)\n", __func__, token);
#endif

    require(token < NBUFFERS, "token is not valid");
    require(resp != NULL, "Resp pointer can not be NULL");

    sharedArea->pool[token].resp = *resp;
}

/* -------------------------------------------------------------------- */

void notifyClient(uint32_t token)
{
#if __DEBUG__
    fprintf(stderr, "%s(token: %u)\n", __func__, token);
#endif

    require(token < NBUFFERS, "Token is not valid");

    BUFFER *b = &sharedArea->pool[token];

    NZ(pthread_mutex_lock(&b->access));
    b->thereIsResponse = true;
    NZ(pthread_cond_signal(&b->responseAvailable));
    NZ(pthread_mutex_unlock(&b->access));
}

/* -------------------------------------------------------------------- */


/* -------------------------------------------------------------------- */
