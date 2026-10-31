library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

entity Program2 is
    Port ( CLK : in STD_LOGIC;
           LED_RED : out STD_LOGIC_VECTOR(3 downto 0);
           LED_GREEN : out STD_LOGIC_VECTOR(3 downto 0));
end Program2;

architecture Behavioral of Program2 is
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

    LED_RED <= (others => toggle);
    LED_GREEN <= "0000";
end Behavioral;
