#include <p18cxxx.h>
#include <spi.h>
// FUNCTION Prototypes
void main(void);
void set_wren(void);
void busy_polling(void);
unsigned char status_read(void);
void status_write(unsigned char data);
void byte_write(unsigned char addhigh,
        unsigned char addlow,
        unsigned char data);
void page_write(unsigned char addhigh,
        unsigned char addlow,
        unsigned char *wrptr);
void array_read(unsigned char addhigh,
        unsigned char addlow,
        unsigned char *rdptr,
        unsigned char count);
unsigned char byte_read(unsigned char addhigh,
        unsigned char addlow);
// VARIABLE Definitions
unsigned char arraywr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0};
//25C040/080/160 page write size
unsigned char arrayrd[16];
unsigned char var;

#define SPI_CS LATCbits.LATC2

//**************************************************

void main(void) {
    TRISCbits.TRISC2 = 0;
    SPI_CS = 1; // ensure SPI memory device
    // Chip Select is reset
    OpenSPI(SPI_FOSC_16, MODE_00, SMPEND);
    set_wren();
    status_write(0);
    busy_polling();
    set_wren();
    byte_write(0x00, 0x61, 'E');
    busy_polling();
    var = byte_read(0x00, 0x61);
    set_wren();
    page_write(0x00, 0x30, arraywr);
    busy_polling();
    array_read(0x00, 0x30, arrayrd, 16);
    var = status_read();
    CloseSPI();
    while (1);
}

void set_wren(void) {
    SPI_CS = 0;
    //assert chip select
    var = putcSPI(SPI_WREN);
    //send write enable command
    SPI_CS = 1;
    //negate chip select
}

void page_write(unsigned char addhigh,
        unsigned char addlow,
        unsigned char *wrptr) {
    SPI_CS = 0;
    //assert chip select
    var = putcSPI(SPI_WRITE);
    //send write command
    var = putcSPI(addhigh);
    //send high byte of address
    var = putcSPI(addlow);
    //send low byte of address
    putsSPI(wrptr);
    //send data byte
    SPI_CS = 1;
    //negate chip select
}

void array_read(unsigned char addhigh,
        unsigned char addlow,
        unsigned char *rdptr,
        unsigned char count) {
    SPI_CS = 0;
    //assert chip select
    var = putcSPI(SPI_READ); //send read command
    var = putcSPI(addhigh); //send high byte of address
    var = putcSPI(addlow);
    //send low byte of address
    getsSPI(rdptr, count);
    //read multiple bytes
    SPI_CS = 1;
}

void byte_write(unsigned char addhigh,
        unsigned char addlow,
        unsigned char data) {
    SPI_CS = 0;
    //assert chip select
    var = putcSPI(SPI_WRITE); //send write command
    var = putcSPI(addhigh);
    //send high byte of address
    var = putcSPI(addlow);
    //send low byte of address
    var = putcSPI(data);
    //send data byte
    SPI_CS = 1;
    //negate chip select
}

unsigned char byte_read(unsigned char addhigh,
        unsigned char addlow) {
    SPI_CS = 0;
    //assert chip select
    var = putcSPI(SPI_READ); //send read command
    var = putcSPI(addhigh);
    //send high byte of address
    var = putcSPI(addlow);
    //send low byte of address
    var = getcSPI();
    //read single byte
    SPI_CS = 1;
    return (var);
}

unsigned char status_read(void) {
    SPI_CS = 0;
    //assert chip select
    var = putcSPI(SPI_RDSR); //send read status command
    var = getcSPI();
    //read data byte
    SPI_CS = 1;
    //negate chip select
    return (var);
}

void status_write(unsigned char data) {
    SPI_CS = 0;
    var = putcSPI(SPI_WRSR); //write status command
    var = putcSPI(data);
    //status byte to write
    SPI_CS = 1;
    //negate chip select
}

void busy_polling(void) {
    do {
        SPI_CS = 0;
        //assert chip select
        var = putcSPI(SPI_RDSR);
        //send read status command
        var = getcSPI();
        //read data byte
        SPI_CS = 1;
        //negate chip select
    } while (var & 0x01);
    //stay in loop until !busy
}
