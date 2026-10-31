library IEEE;
use IEEE.std_logic_1164.all;

entity nandgate is
port ( inport0 : in std_logic;
		inport1 : in std_logic;
		outport : out std_logic);
end nandgate;

architecture structural of nandgate is

		signal s_outportAnd : std_logic;
		
		begin

and0 :entity work.and2gate(behavioral) 
			port map (	inport0 => inport0,
							inport1 => inport1,
							outport => s_outportAnd);

				
not0: entity work.NOTgate(behavioral)
			port map (	inport => s_outportAnd,
								outport => outport );
end structural;					