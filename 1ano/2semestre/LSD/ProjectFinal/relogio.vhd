-- Bloco do Relógio
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity relogio is
    Port ( Clock : in STD_LOGIC;
           RESET : in STD_LOGIC;
           ajustar : in STD_LOGIC;
           hora_atual : out INTEGER range 0 to 1439); -- Minutos em um dia
end relogio;

architecture Behavioral of relogio is
    signal hora : INTEGER range 0 to 1439 := 0;
begin
    process(Clock, RESET)
    begin
        if RESET = '1' then
            hora <= 0;
        elsif rising_edge(Clock) then
            if ajustar = '1' then
                if KEY1 = '1' then
                    hora <= hora + 1;
                elsif KEY2 = '1' then
                    hora <= hora - 1;
                end if;
            else
                hora <= hora + 1; -- Incrementa 1 minuto (1 segundo no tempo real)
                if hora = 1440 then -- Reinicia à meia-noite
                    hora <= 0;
                end if;
            end if;
        end if;
    end process;
    hora_atual <= hora;
end Behavioral;
