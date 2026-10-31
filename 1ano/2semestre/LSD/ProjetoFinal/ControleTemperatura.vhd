library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ControleTemperatura is
    Port (
        temp_media : in std_logic_vector(7 downto 0);
        temp_atual : in std_logic_vector(7 downto 0);
        clock : in std_logic;
        reset : in std_logic;
        estado_resistencia : out std_logic;
        temp_atual_out : out std_logic_vector(7 downto 0)
    );
end ControleTemperatura;

architecture Behavioral of ControleTemperatura is
    signal temp_atual_internal : std_logic_vector(7 downto 0) := "00010100"; -- 20 °C inicial
    signal heating : std_logic := '0';
begin

    process(clock, reset)
    begin
        if reset = '1' then
            temp_atual_internal <= "00010100"; -- 20 °C inicial
            heating <= '0';
        elsif rising_edge(clock) then
            if heating = '1' then
                temp_atual_internal <= temp_atual_internal + 1; -- Aumento de 10 °C/min
                if temp_atual_internal >= (temp_media + 2) then
                    heating <= '0';
                end if;
            else
                temp_atual_internal <= temp_atual_internal - 1; -- Diminuição de 5 °C/min
                if temp_atual_internal <= (temp_media - 2) then
                    heating <= '1';
                end if;
            end if;
        end if;
    end process;

    estado_resistencia <= heating;
    temp_atual_out <= temp_atual_internal;

end Behavioral;