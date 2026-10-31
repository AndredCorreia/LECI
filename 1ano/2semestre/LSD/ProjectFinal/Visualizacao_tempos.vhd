-- Visualização dos Tempos
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity visualizacao_tempos is
    Port ( TD, TF, Time : in INTEGER range 0 to 999;
           HEX0, HEX1, HEX2, HEX3 : out STD_LOGIC_VECTOR(6 downto 0));
end visualizacao_tempos;

architecture Behavioral of visualizacao_tempos is
begin
    process(TD, TF, Time)
    begin
        -- Atribuição simplificada, transformar para BCD e controlar os displays HEX
        HEX0 <= std_logic_vector(to_unsigned(Time mod 10, 7));
        HEX1 <= std_logic_vector(to_unsigned((Time / 10) mod 10, 7));
        HEX2 <= std_logic_vector(to_unsigned((Time / 100) mod 10, 7));
        HEX3 <= std_logic_vector(to_unsigned((Time / 1000) mod 10, 7));
    end process;
end Behavioral;
