library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Programa4 is
    Port ( 
        LEDR : out STD_LOGIC_VECTOR(3 downto 0);
        CLK    : in  STD_LOGIC;            
        LEDG : out STD_LOGIC_VECTOR(3 downto 0)
    );
end Programa4;

architecture Behavioral of Programa4 is
    constant CLOCK_FREQ : integer := 50000000; 
    constant HALF_SECOND : integer := CLOCK_FREQ / 2; 
    signal counter : integer range 0 to CLOCK_FREQ - 1 := 0; 
    signal red_state : boolean := true; 
    signal green_state : boolean := false; 
    signal blink_counter : integer range 0 to CLOCK_FREQ - 1 := 0; 
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            counter <= counter + 1;
            
            if counter < 5 * HALF_SECOND then
                LEDR <= "0000";
            else
                if red_state then
                    LEDR <= "1111";
                else
                    LEDR <= "0000";
                end if;
                
                if counter mod (CLOCK_FREQ / 2) = 0 then
                    red_state <= not red_state;
                end if;
            end if;
            
            if counter < 5 * HALF_SECOND then
                if blink_counter < HALF_SECOND then
                    LEDG <= "0000";
                else
                    LEDG <= "1111";
                end if;
                
                blink_counter <= blink_counter + 1;
                
                if blink_counter = CLOCK_FREQ then
                    blink_counter <= 0;
                end if;
            else
                LEDG <= "0000";
            end if;
            
            if counter = 10 * HALF_SECOND then
                counter <= 0;
            end if;
        end if;
    end process;
end Behavioral;
