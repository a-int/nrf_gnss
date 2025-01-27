#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#define BUFFER_SIZE (1024)  // Buffer size for incoming data

static const struct device *uart1_dev = DEVICE_DT_GET(DT_NODELABEL(uart2));
static uint8_t rx_buffer[BUFFER_SIZE];  // Buffer for received data
static volatile size_t rx_len = 0;      // Received data length

void uart1_callback(const struct device *dev, struct uart_event *evt, void *user_data) {
    switch (evt->type) {
    case UART_RX_RDY:  // Data is ready to be processed
        printk("%s", evt->data.rx.buf);
        break;
    default:
        break;
    }
    uart_rx_enable(uart1_dev, rx_buffer, sizeof(rx_buffer), 100000);
}

void main(void) {
    if (!device_is_ready(uart1_dev)) {
        printk("Device not ready\r\n");
        return;
    }

    printk("uart cb set ret %d\r\n", uart_callback_set(uart1_dev, uart1_callback, NULL));
    printk("uart rx en ret %d\r\n", uart_rx_enable(uart1_dev, rx_buffer, sizeof(rx_buffer), 100000));
}