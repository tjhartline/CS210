#Tammy Hartline
#12/04/2022-12/11/2022

from ast import Global, Str
from collections import Counter, defaultdict
from linecache import getlines
from operator import contains
import re
import string
from typing import ItemsView

#empty dict to store items
Global 
itemDictionary = {}
#empty list
Global
eachItemList = []


#menu display function

def MenuDisplay():

	print("		<<----------------------------------------------->>")
	print("		|^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^|")
	print("		|^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^|")
	print("		|                                                 |")
	print("		|                  MENU CHOICES                   |")
	print("		|                                                 |")
	print("		|^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^|")
	print("		|                                                 |")
	print("		|                                                 |")
	print("		|  [1]   List All Items Purchased                 |")
	print("		|  [2]   Lookup Item Purchase Frequency Per Date  |")
	print("		|  [3]   Create File & Histogram for All Items    |")
	print("		|  [4]   Exit Program                             |")
	print("		|                                                 |")
	print("		|                                                 |")
	print("		|^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^|")
	print("		|^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^o^|")
	print("		<<----------------------------------------------->>")
	print("		|          ~ Enter your menu selection ~          |")
	print("		<<_______________________________________________>>\n")

#end of MenuDisplay() print function


#create dictionary and function that will read item file

def CreateList():

    with open ('Project3Py.txt') as itemList:
        storeItemsList = itemList.readlines()
        storeItemsList.sort()  #sort list alphabetically 

        #for loop to remove/ignore whitespace and newlines while adding to list
        for eachItem in storeItemsList:

            eachItemList.append(eachItem.strip('\n'))

        #for loop to add item to dict as key and count
        for eachItem in eachItemList:

            #if item is already in dictionary add to count per time item appears
            if eachItem in itemDictionary.keys():
                
                countItem = itemDictionary[eachItem]
                itemDictionary[eachItem] = countItem + 1

            else:
                 itemDictionary[eachItem] = 1


#end of CreateList function



#Process to call in C++: CallProcedure("CountUnique") for menu option 1
def UserOption1():


    
    #call CreateList
    CreateList()
    #output name based on user menu selection of 1
    print(" <<<<<<<<<<<<<<<<<<<<<<|***|>>>>>>>>>>>>>>>>>>>>>\n")
    print("|*~*~*~*~*~*     Menu Selection 1     *~*~*~*~*~*|\n")
    print("|*~*~*~*~*~*    Iventory Purchased    *~*~*~*~*~*|\n")
    print(" <<<<<<<<<<<<<<<<<<<<<<|***|>>>>>>>>>>>>>>>>>>>>>\n")

    #format output for menu selection
    format_string = '{item:^18}{qty:.14}'
    print(format_string.format(item='Item Inventory',qty='|   Item Total'))
    
    print(" ***********************************************")
    print()
    format_string ='{item:>14}{qty:>14}'

    for eachItem, count in itemDictionary.items():    #for loop to print each item and times purchased

        print(format_string.format(item=eachItem,qty=count))
       
    print('\n')
    MenuDisplay()
#end of CountUnique function for when menu selection from user is 1
#Process to call function: callIntFunction("CountSelected",itemSearch) for menu option 2

def UserOption2 ():

    itemSelection = input("Enter your selected item to check the frequency of it purchase: ")
    openTxt = open("Project3Py.txt")
    freqCount = 0
    print('\n')

    for item in openTxt:

        item = item.strip()
        word = item.lower()

        if word == itemSelection.lower():

            freqCount += 1

    if freqCount >= 1:

        print("Your item: ", itemSelection, ", was purchased ", freqCount, "time(s) today.\n")
        MenuDisplay()
    
   
    if freqCount <= 0:
        print("Sorry, your entered item was not purchased today.\n")
        MenuDisplay()

#end of UserOption2 function

#Process to call function: CallProcedure("PrintHistogram") for menu option 3
def UserOption3():

    #call CreateList function
   CreateList()

    #open frequency.dat file
   with open('frequency.dat', 'w') as histogram:



      for key in itemDictionary.keys():

        histogram.write('{} {}'.format(key, itemDictionary.get(key))) #format write
      
      
   


#end of PrintHistogram function