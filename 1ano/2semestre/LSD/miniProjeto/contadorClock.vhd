library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity contadorClock is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           switch : in STD_LOGIC;
           LED : out STD_LOGIC_VECTOR (3 downto 0);
           segment_display : out STD_LOGIC_VECTOR (6 downto 0));
end contadorClock;

architecture Behavioral of contadorClock is
    signal count_value : integer range 0 to 11 := 0;
    signal display_value : integer range 0 to 11 := 0;
    signal clock_counter : integer range 0 to 49999999 := 0; -- Assuming 50 MHz clock
    signal LED_control : STD_LOGIC := '0';
    signal display_control : STD_LOGIC := '1';

begin
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                clock_counter <= 0;
            else
                clock_counter <= clock_counter + 1;
            end if;
        end if;
    end process;

    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                count_value <= 0;
            elsif clock_counter = 49999999 then
                count_value <= count_value + 1;
                clock_counter <= 0;
            end if;
        end if;
    end process;

    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                LED_control <= '0';
            elsif clock_counter = 12499999 then
                LED_control <= not LED_control;
                clock_counter <= 0;
            end if;
        end if;
    end process;

    process(clk)
    begin
        if rising_edge(clk) then
            if switch = '1' then
                display_control <= '0';
            else
                display_control <= '1';
            end if;
        end if;
    end process;

    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                display_value <= 0;
            elsif count_value = 11 then
                display_value <= 0;
            else
                display_value <= count_value + 1;
            end if;
        end if;
    end process;

    LED <= (others => LED_control);
    segment_display <= "0000000";

    

end Behavioral;
