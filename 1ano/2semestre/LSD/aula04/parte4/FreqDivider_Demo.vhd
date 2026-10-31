library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity FreqDivider_Demo is
end FreqDivider_Demo;

architecture Behavioral of FreqDivider_Demo is
    component FreqDivider is
        port (
            clkIn  : in  std_logic;
            clkOut : out std_logic
        );
    end component;
    
    signal clkIn_signal : std_logic := '0'; 
    signal clkOut_signal : std_logic; 
    
    constant k_value : std_logic_vector(31 downto 0) := x"017D7840"; 
    
    signal LEDR : std_logic_vector(7 downto 0) := (others => '0'); 

begin
    Divider_Instance : FreqDivider
    port map (
        clkIn  => clkIn_signal,
        clkOut => clkOut_signal
    );
    
    -- Processo para simular o sinal de relógio
    process
    begin
        -- Simulando o CLOCK_50 da placa de desenvolvimento
        while true loop
            clkIn_signal <= not clkIn_signal;
            wait for 10 ns; -- Atraso para simular o relógio
        end loop;
    end process;
    
    -- Inverte o sinal de clkOut para acionar o LEDR
    LEDR <= (not clkOut_signal);

end Behavioral;
