library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity AjusteRegistro is
    Port (
        sw1 : in std_logic;
        sw2 : in std_logic;
        KEY1 : in std_logic;
        KEY2 : in std_logic;
        clock : in std_logic;
        reset : in std_logic;
        TD : out std_logic_vector(7 downto 0);
        TF : out std_logic_vector(7 downto 0);
        temp_media : out std_logic_vector(7 downto 0);
        relogio : out std_logic_vector(7 downto 0);
        display_output : out std_logic_vector(6 downto 0)
    );
end AjusteRegistro;

architecture Behavioral of AjusteRegistro is
    signal temp_TD : std_logic_vector(7 downto 0) := "00000000";
    signal temp_TF : std_logic_vector(7 downto 0) := "00000000";
    signal temp_temp_media : std_logic_vector(7 downto 0) := "00000000";
    signal temp_relogio : std_logic_vector(7 downto 0) := "00000000";
    signal ajuste_parametro : std_logic_vector(1 downto 0);
begin

    process(clock, reset)
    begin
        if reset = '1' then
            temp_TD <= "00000000";
            temp_TF <= "00000000";
            temp_temp_media <= "00000000";
            temp_relogio <= "00000000";
elsif rising_edge(clock) then
            ajuste_parametro <= sw1 & sw2;
            case ajuste_parametro is
                when "00" => 
                    if KEY1 = '1' then
                        temp_temp_media <= temp_temp_media + 1;
                    elsif KEY2 = '1' then
                        temp_temp_media <= temp_temp_media - 1;
                    end if;
                    display_output <= temp_temp_media(6 downto 0);
                when "01" => 
                    if KEY1 = '1' then
                        temp_TD <= temp_TD + 1;
                    elsif KEY2 = '1' then
                        temp_TD <= temp_TD - 1;
                    end if;
                    display_output <= temp_TD(6 downto 0);
                when "10" => 
                    if KEY1 = '1' then
                        temp_TF <= temp_TF + 1;
                    elsif KEY2 = '1' then
                        temp_TF <= temp_TF - 1;
                    end if;
                    display_output <= temp_TF(6 downto 0);
                when "11" => 
                    if KEY1 = '1' then
                        temp_relogio <= temp_relogio + 1;
                    elsif KEY2 = '1' then
                        temp_relogio <= temp_relogio - 1;
                    end if;
                    display_output <= temp_relogio(6 downto 0);
                when others =>
                    display_output <= "0000000";
            end case;
        end if;
    end process;

    TD <= temp_TD;
    TF <= temp_TF;
    temp_media <= temp_temp_media;
    relogio <= temp_relogio;

end Behavioral;