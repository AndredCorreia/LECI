library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity RelogioForno is
    Port (
        adjust_signal : in std_logic;
        clock : in std_logic;
        reset : in std_logic;
        relogio_out : out std_logic_vector(7 downto 0)
    );
end RelogioForno;

architecture Behavioral of RelogioForno is
    signal relogio_internal : std_logic_vector(7 downto 0) := "00000000";
begin

    process(clock, reset)
    begin
        if reset = '1' then
            relogio_internal <= "00000000";
        elsif rising_edge(clock) then
            if adjust_signal = '1' then
                relogio_internal <= relogio_internal + 1;
            else
                relogio_internal <= relogio_internal;
            end if;
        end if;
    end process;

    relogio_out <= relogio_internal;

end Behavioral;