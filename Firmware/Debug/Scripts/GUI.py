#   _    _ _______   __  __ _____ _____ _____   ____  _   _
#  | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
#  | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
#  |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
#  | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
#  |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
#  =================== Advanced R&D ========================

#  Copyright (c) 2023 HT Micron Semicondutores S.A.
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#  http://www.apache.org/licenses/LICENSE-2.0
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

# file: GUI.py
# brief: GUI backend used for COM port selection. 
# author: HT Micron Advanced R&D
# link: https://github.com/htmicron
# version: 0.1
# date: February 23, 2023

import sys
import serial
import glob

from PyQt5 import QtWidgets

from COM_GUI import Ui_MainWindow

class Backend(QtWidgets.QMainWindow, Ui_MainWindow):
    
    def __init__(self) -> None:
        super(Backend, self).__init__()

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.pushButton.clicked.connect(self.push_button_clicked)

        self.init_com_ports()

    def keyPressEvent(self, event):
        self.update_com_file(str(self.ui.comboBox.currentText()))
        sys.exit()

    def push_button_clicked(self):
        self.update_com_file(str(self.ui.comboBox.currentText()))
        sys.exit()

    def update_com_file(self, com_port):
        with open("Debug/COM.txt", "w") as file:
            file.write(com_port)
        
        file.close()

    def init_com_ports(self):
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                self.ui.comboBox.addItem(port)
            except (OSError, serial.SerialException):
                pass

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = Backend()
    window.show()
    sys.exit(app.exec_())