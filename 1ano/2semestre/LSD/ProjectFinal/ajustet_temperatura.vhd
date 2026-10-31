-- Ajuste e Registo da Temperatura Média
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ajuste_temperatura is
    Port ( sw1 : in STD_LOGIC;
           sw2 : in STD_LOGIC;
           KEY1 : in STD_LOGIC;
           KEY2 : in STD_LOGIC;
           Clock : in STD_LOGIC;
           RESET : in STD_LOGIC;
           temp_media : out INTEGER range 0 to 999);
end ajuste_temperatura;

architecture Behavioral of ajuste_temperatura is
    signal temp : INTEGER range 0 to 999 := 0;
    signal adjusting : STD_LOGIC := '0';
begin
    process(Clock, RESET)
    begin
        if RESET = '1' then
            temp <= 0;
        elsif rising_edge(Clock) then
            if sw1 = '0' and sw2 = '0' then -- Ajuste de Temperatura Média
                adjusting <= '1';
                if KEY1 = '1' then
                    temp <= temp + 1;
                elsif KEY2 = '1' then
                    temp <= temp - 1;
                end if;
            else
                adjusting <= '0';
            end if;
        end if;
    end process;
    temp_media <= temp;
end Behavioral;
