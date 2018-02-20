If you want to simply flash binary files to arbitrary sections of memory, or read arbitary addresses of memory out to a binary file, use the st-flash tool, as shown below:

# stlink command

$> ./st-flash write main.bin 0x8000000