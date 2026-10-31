library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity BlinkGenerator is
    generic (
        NUMBER_STEPS : positive := 12_500_000
    );
    port (
        clk   : in  STD_LOGIC;
        reset : in  STD_LOGIC;
        blink : out STD_LOGIC
    );
end BlinkGenerator;

architecture Behavioral of BlinkGenerator is
    signal counter : natural range 0 to NUMBER_STEPS - 1;
begin
    count_process: process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' or counter >= NUMBER_STEPS - 1 then
                counter <= 0;
            else
                counter <= counter + 1;
            end if;
        end if;
    end process count_process;

    blink <= '1' when counter >= (NUMBER_STEPS / 2) else '0';
end Behavioral;
