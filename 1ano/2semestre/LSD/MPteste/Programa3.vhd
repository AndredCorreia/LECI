library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.all;

entity Programa3 is
    Port ( 
        CLK : in STD_LOGIC;
        LEDR : out STD_LOGIC_VECTOR(3 downto 0);
        LEDG : out STD_LOGIC_VECTOR(3 downto 0)
    );
end Programa3;

architecture Behavioral of Programa3 is
    constant CLOCK_FREQUENCY : natural := 50000000;
    constant HALF_SECOND : natural := CLOCK_FREQUENCY / 2;
    signal counter : unsigned(23 downto 0) := (others => '0');
    signal toggle : std_logic := '0';
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            counter <= counter + 1;
            if counter = HALF_SECOND then
                toggle <= not toggle;
                counter <= (others => '0');
            end if;
        end if;
    end process;

    LEDR <= "0000";
    LEDG <= (others => toggle);
end Behavioral;
