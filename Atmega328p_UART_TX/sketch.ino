#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define clock frequency (16 MHz for ATmega328P)
#define BAUD 9600         // Desired baud rate
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1) // Calculate UBRR value

// Initialize UART
void uart_init(void) {
    // Set baud rate
    UBRR0H = (UBRR_VALUE >> 8); // Upper 8 bits of UBRR
    UBRR0L = UBRR_VALUE;        // Lower 8 bits of UBRR

    // Enable transmitter (TX)
    UCSR0B = (1 << TXEN0);

    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Transmit a single byte over UART
void uart_transmit(char data) {
    // Wait for the transmit buffer to be empty
    while (!(UCSR0A & (1 << UDRE0)));

    // Send the data
    UDR0 = data;
}

// Transmit a string over UART
void uart_print(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

int main(void) {
    uart_init(); // Initialize UART

    while (1) {
        uart_print("Hello, UART Debugging!\r\n"); // Send message
        _delay_ms(1000); // Wait 1 second
    }

    return 0;
}
