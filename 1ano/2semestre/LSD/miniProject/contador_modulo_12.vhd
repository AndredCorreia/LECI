library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity contador_modulo_12 is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           switch : in STD_LOGIC;
           LED : out STD_LOGIC_VECTOR (3 downto 0);
           segment_display : out STD_LOGIC_VECTOR (6 downto 0));
end contador_modulo_12;

architecture Behavioral of contador_modulo_12 is
    signal count_value : integer range 0 to 11 := 0;
    signal display_value : integer range 0 to 11 := 0;
    signal clock_counter : integer range 0 to 49999999 := 0; -- Assuming 50 MHz clock
    signal LED_control : STD_LOGIC := '0';
    signal display_control : STD_LOGIC := '1'; -- Inicia exibindo o valor do contador

begin
    -- Contador de Clock
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

    -- Contador Módulo 12
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                count_value <= 0;
            elsif clock_counter = 49999999 then -- Aproximadamente 1 segundo
                count_value <= count_value + 1;
                clock_counter <= 0;
            end if;
        end if;
    end process;

    -- Controle de LEDs
    process(clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                LED_control <= '0';
            elsif clock_counter = 12499999 then -- Aproximadamente 4 vezes por segundo
                LED_control <= not LED_control;
                clock_counter <= 0;
            end if;
        end if;
    end process;

    -- Controle de exibição
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

    -- Atualização do valor a ser exibido
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

    -- Saída para LEDs e display de 7 segmentos
    LED <= (others => LED_control);
    segment_display <= "0000000"; -- Mapeamento de 7 segmentos para dígitos
    -- Ajuste do valor a ser exibido no display de 7 segmentos
    case display_value is
        when 0 =>
            segment_display <= "0111111"; -- "0"
        when 1 =>
            segment_display <= "0000110"; -- "1"
        when 2 =>
            segment_display <= "1011011"; -- "2"
        when 3 =>
            segment_display <= "1001111"; -- "3"
        when 4 =>
            segment_display <= "1100110"; -- "4"
        when 5 =>
            segment_display <= "1101101"; -- "5"
        when 6 =>
            segment_display <= "1111101"; -- "6"
        when 7 =>
            segment_display <= "0000111"; -- "7"
        when 8 =>
            segment_display <= "1111111"; -- "8"
        when 9 =>
            segment_display <= "1101111"; -- "9"
        when 10 =>
            segment_display <= "1110111"; -- "A"
        when 11 =>
            segment_display <= "1111100"; -- "b"
        when others =>
            segment_display <= "1111111"; -- Valor padrão: "8"
    end case;

end Behavioral;
