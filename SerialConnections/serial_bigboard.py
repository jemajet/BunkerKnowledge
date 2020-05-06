import sys
sys.path.insert(1, "../RetrievalSystem")
from processing import *
from retrieval import *
import serial
import time
import threading

# with serial.Serial("COM3", 9600) as ser:
#	 print("Welcome to serial connection sexy")
#	 while True:
#		 val = commandut(" > ")
#		 if val.lower() == "exit":
#			 break
#		 ser.write(val.encode())


class Serial_Control():

    def __init__(self, port, baud_rate):
        self.dataset = Covid19_Dataset()
        self.port = port
        self.baud_rate = baud_rate
        self.big_board_serial = None
        self.line_reader = None

    def start(self):
        print("Send start to begin Covid-19 Database")
        while self.get_command() != "start":
            pass
        self.big_board_serial = serial.Serial(self.port, self.baud_rate)
        self.line_reader = ReadLine(self.big_board_serial)
        print("hey")
        self.startup()
        self.terminal()

    def startup(self):
        print("\n  **********************************************")
        print("  * Welcome to the Covid-19 Database Terminal! *")
        print("  **********************************************\n")
        print("-Please wait for startup (could take up to 10 seconds)")
        print("-To get help, please type help\nSending data...")
        # print("Sending data", end="")
        # self.transmit_node(self.dataset.get_current("TX"))
        # print(self.dataset.get_current("TX"))
        # nodes = self.dataset.get_all_current().values()
        # self.transmit_nodes(nodes)

    def transmit_nodes(self, nodes):
        # Sends nodes to the serial port, displays a progress bar with 5
        # periods
        # total_nodes = len(nodes)
        # num_per_print = 10
        sent = "".join([node.transmit_string() for node in nodes])

        # for i, node in enumerate(nodes):
        #	 self.transmit_node(node)
        # if i % num_per_print == 0:
        #	 print(".", end="")
        # print()

    def transmit_node(self, node):
        self.transmit_word(node.transmit_string())

    def transmit_word(self, string):
        self.big_board_serial.write(string.encode())

    def terminal(self):
        while True:
            command = self.get_command()
            self.transmit_word(command)
            # self.transmit_word("\n")
            response = self.line_reader.readline().decode("utf-8")
            print(response, end="")
            if command == "exit":
                break
            elif command == "help":
                self.help()
            else:
                pass
                # print(command)
            self.big_board_serial.write(command.encode())
        self.big_board_serial.close()

    def get_command(self):
        return input(" > ").lower()

    def help(self):
        help_file = "help_file.txt"
        with open(help_file, "r") as f:
            text = f.read()
            print(text)

    # def parse(self, )


class ReadLine:

    def __init__(self, s):
        self.buf = bytearray()
        self.s = s

    def readline(self):
        i = self.buf.find(b"\n")
        if i >= 0:
            r = self.buf[:i + 1]
            self.buf = self.buf[i + 1:]
            return r
        while True:
            i = max(1, min(2048, self.s.in_waiting))
            data = self.s.read(i)
            i = data.find(b"\n")
            if i >= 0:
                r = self.buf + data[:i + 1]
                self.buf[0:] = data[i + 1:]
                return r
            else:
                self.buf.extend(data)


if __name__ == "__main__":
    port = "COM3"
    baud = 57600  # look into why 115200 is producing weird stuff
    connection = Serial_Control(port, baud)
    connection.start()
    # print(connection.dataset.get_current("TX"))
    # print(connection.dataset.get_current("MA"))
    # con = serial.Serial(port, baud)
    # s = ReadLine(con)
    # while True:
    #     r = s.readline()
    #     print(r.decode("utf-8"), end="")
