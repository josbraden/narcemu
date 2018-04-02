# Comments are remaining line length and begin with '#' or '//'
# Program must start with .data segment
.data
word	x		# Only supported data type by NARC is word
word	vari
# Program must also contain .text segment
.text
RDW					# A zero-address instruction
STW			x		# A one-address instruction
LDX			1 x		# An index instruction: the index register followed by the memory location
label1:				# A label to jump to
RDW
BIP			exit	# A conditional jump, conditions all rely on ACC register
BRU			label	# An unconditional jump
exit:
HLT					# Ending HLT instruction
