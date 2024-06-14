import time
import matplotlib.pyplot as plt

DEVICE_FILE = "/dev/gpio_driver_test"

def read_gpio_signal():
    with open(DEVICE_FILE, 'r') as file:
        lines = file.read().strip().split('\n')
    signal = int(lines[0].split(': ')[1])
    return signal

def select_signal(signal):
    with open(DEVICE_FILE, 'w') as file:
        file.write("{}".format(signal))

def main():
    print("Select the GPIO PIN to read:")
    print("1: GPIO_PIN1")
    print("2: GPIO_PIN2")
    selected_signal = int(input("Enter 1 or 2:"))
    select_signal(selected_signal)

    data = []
    timestamps = []

    start_time = time.time()
    try:
        while True:
            signal = read_gpio_signal()
            current_time = time.time() - start_time

            timestamps.append(current_time)
            data.append(signal)

            time.sleep(0.1)

            plt.clf()
            plt.plot(timestamps, data, label='Signal {}'.format(selected_signal))
            plt.xlabel('Time (s)')
            plt.ylabel('Signal')
            plt.title('GPIO Signal {}'.format(selected_signal))
            plt.legend()
            plt.pause(0.01)

    except KeyboardInterrupt:
        pass

    plt.show()

if __name__ == "__main__":
    main()
