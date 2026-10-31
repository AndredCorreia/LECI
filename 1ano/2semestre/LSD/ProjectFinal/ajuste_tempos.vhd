-- Ajuste e Registo de Tempos (TD, TF)
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ajuste_tempos is
    Port ( sw1 : in STD_LOGIC;
           sw2 : in STD_LOGIC;
           KEY1 : in STD_LOGIC;
           KEY2 : in STD_LOGIC;
           Clock : in STD_LOGIC;
           RESET : in STD_LOGIC;
           TD : out INTEGER range 0 to 999;
           TF : out INTEGER range 0 to 999);
end ajuste_tempos;

architecture Behavioral of ajuste_tempos is
    signal temp_TD : INTEGER range 0 to 999 := 0;
    signal temp_TF : INTEGER range 0 to 999 := 0;
    signal adjusting : STD_LOGIC := '0';
begin
    process(Clock, RESET)
    begin
        if RESET = '1' then
            temp_TD <= 0;
            temp_TF <= 0;
        elsif rising_edge(Clock) then
            if sw1 = '0' and sw2 = '1' then -- Ajuste de TD
                adjusting <= '1';
                if KEY1 = '1' then
                    temp_TD <= temp_TD + 1;
                elsif KEY2 = '1' then
                    temp_TD <= temp_TD - 1;
                end if;
            elsif sw1 = '1' and sw2 = '0' then -- Ajuste de TF
                adjusting <= '1';
                if KEY1 = '1' then
                    temp_TF <= temp_TF + 1;
                elsif KEY2 = '1' then
                    temp_TF <= temp_TF - 1;
                end if;
            else
                adjusting <= '0';
            end if;
        end if;
    end process;
    TD <= temp_TD;
    TF <= temp_TF;
end Behavioral;
