-- Bloco de Controle do Display
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity controle_display is
    Port ( temp_atual : in INTEGER range 0 to 999;
           temp_media : in INTEGER range 0 to 999;
           Clock : in STD_LOGIC;
           HEX4, HEX5, HEX6 : out STD_LOGIC_VECTOR(6 downto 0));
end controle_display;

architecture Behavioral of controle_display is
begin
    process(temp_atual, temp_media)
    begin
        -- Atribuição simplificada, transformar para BCD e controlar os displays HEX
        HEX4 <= std_logic_vector(to_unsigned(temp_atual mod 10, 7));
        HEX5 <= std_logic_vector(to_unsigned((temp_atual / 10) mod 10, 7));
        HEX6 <= std_logic_vector(to_unsigned(temp_atual / 100, 7));
    end process;
end Behavioral;
