-- Bloco de Controle de Temperatura
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity controle_temperatura is
    Port ( temp_media : in INTEGER range 0 to 999;
           Clock : in STD_LOGIC;
           RESET : in STD_LOGIC;
           resistencia : out STD_LOGIC;
           temp_atual : out INTEGER range 0 to 999);
end controle_temperatura;

architecture Behavioral of controle_temperatura is
    signal temp : INTEGER range 0 to 999 := 20; -- Temperatura ambiente inicial
    signal heating : STD_LOGIC := '0';
begin
    process(Clock, RESET)
    begin
        if RESET = '1' then
            temp <= 20;
            heating <= '0';
        elsif rising_edge(Clock) then
            if heating = '1' then
                temp <= temp + 10; -- Aumenta 10 °C/min
                if temp >= temp_media + 2 then
                    heating <= '0';
                end if;
            else
                temp <= temp - 5; -- Diminui 5 °C/min
                if temp <= temp_media - 2 then
                    heating <= '1';
                end if;
            end if;
        end if;
    end process;
    resistencia <= heating;
    temp_atual <= temp;
end Behavioral;
