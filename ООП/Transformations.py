from ctypes import *
import numpy as np
import sys

libc = CDLL("./Dll1.dll")

#Задаем првильные форматы функциям
libc.create_simple_object.restype = c_void_p
libc.create_simple_object.argtypes = [c_double, c_double, c_double, c_double]
libc.obj_print_self.argtypes = [c_void_p]

libc.create_Moving.restype = c_void_p
libc.create_Moving.argtypes = [c_double, c_double, c_double, c_double, c_char_p]

libc.transform.restype = c_void_p
libc.transform.argtypes = [c_void_p, c_void_p]


Array_simple_type = c_double*4

libc.simple_object_values.restype = POINTER(Array_simple_type)
libc.simple_object_values.argtypes = [c_void_p]

libc.delete_simple_object.restype = c_void_p
libc.delete_simple_object.argtypes = [c_void_p]

libc.delete_transformation.restype = c_void_p
libc.delete_transformation.argtypes = [c_void_p]

libc.create_operation_list.restype = c_void_p
libc.add_to_op_list.argtypes = [c_void_p, c_void_p]
libc.delete_op_list = [c_void_p]

libc.create_obj_list.restype = c_void_p
libc.add_to_obj_list.argtypes = [c_void_p, c_void_p, c_char_p]
libc.delete_object_list = [c_void_p]

libc.create_tr_programm.restype = c_void_p
libc.create_tr_programm.argtypes = [c_void_p, c_void_p]
libc.add_to_prog.argtypes = [c_void_p, c_char_p, c_char_p, c_char_p]
libc.execute_programm.argtypes = [c_void_p]
libc.delete_programm.argtypes = [c_void_p]

libc.obj_from_list.argtypes = [c_void_p, c_char_p]
libc.obj_from_list.restype = c_void_p
#Начинаем делать что-то значащее

def get_nymber():
    while True:
        try:
            num = float(input("Enter number:"))
            return num
        except ValueError:
            print("This value is incorrect.")

def create_mov(Operation_list):
    print("Введите координаты")
    x = get_nymber()
    y = get_nymber()
    z = get_nymber()
    w = get_nymber()
    m_id = input("Enter id")
    mov_id = c_char_p(m_id.encode('utf-8'))

    mov = libc.create_Moving(x,y,z,w,mov_id)
    if mov == None:
        print("Wrong input")
        return -1
    libc.add_to_op_list(Operation_list, mov)
    return 0

def create_simple_obj(Object_list):
    print("Введите координаты")
    x = get_nymber()
    y = get_nymber()
    z = get_nymber()
    w = get_nymber()
    n = input("Введите имя")
    name = c_char_p(n.encode('utf-8'))

    obj = libc.create_simple_object(x,y,z,w)
    libc.add_to_obj_list(Object_list, obj, name)
    return 0

def add_to_prog(Tr_programm):
    tr = input("Введите имя преобразования")
    arg = input("Введите имя аргумента")
    res = input("Введите куда записать результат")

    
    trans = c_char_p(tr.encode('utf-8'))
    argum = c_char_p(arg.encode('utf-8'))
    result = c_char_p(res.encode('utf-8'))

    libc.add_to_prog(Tr_programm, trans, argum, result)
    return 0

def execute(Tr_programm):
    return libc.execute_programm(Tr_programm)

def read(Object_list):
    arg = input("Введите имя переменной:")
    arg = c_char_p(arg.encode('utf-8'))

    obj = libc.obj_from_list(Object_list, arg)
    #print("Результат:")
    return np.frombuffer(libc.simple_object_values(obj).contents)

def user_handler():
    
    Object_list = libc.create_obj_list()
    Operation_list = libc.create_operation_list()
    Tr_programm = libc.create_tr_programm(Operation_list, Object_list)
    msg = "Press 1 to create object \n Press 2 to create operation \n Press 3 to add operation in queue \n Press 4 to execute programm \n Press h for help \n Press 5 to read object \n Press 6 to exit"
    print(msg)
    while True:
        num = input("Введите команду:")
        if(num == '1'):
            create_simple_obj(Object_list)
            continue
        if(num == '2'):
            create_mov(Operation_list)
            continue
        if(num == '3'):
            add_to_prog(Tr_programm)
            continue
        if(num == '4'):
            execute(Tr_programm)
            continue
        if(num == '5'):
            n = read(Object_list)
            print(n)
            continue
        if(num == '6'):
            libc.delete_programm(Tr_programm)

            #По непонятным причинам ctypes считает libc.delete_op_list классом, а не функцией
            #libc.delete_op_list(Operation_list)
            #libc.delete_object_list(Object_list)
            return 0
        if(num == 'h'):
            print(msg)
        else:
            print("Wrong input")



    
sys.stdin = open('test.txt', 'r')
user_handler()
sys.stdin.close()

