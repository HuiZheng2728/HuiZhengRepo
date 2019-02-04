
#1.User provides an ip address,validate the input
#2.User provides a ip mask ,validate the mask
#3.Split the mask into a list ,convert elements in the list to binary
   #append/join the binary result to a new string
#4.Calculate the wildcard_mask,convert it to decimal form
#5.Convert ip to binary,then calculate network ip adrr and broadcast ip addr in binary
   #convert them to decimal ip form
#6. Use random to generate random ip with range from network ip addr to broadcast ip addr

import random
import sys


def convert_binary(octets,octets_binary):
    for oct in octets:
        binary_octet = bin(int(oct)).lstrip('0b')
        octets_binary.append(binary_octet.zfill(8))
    return octets_binary

def convert_address(octets,address_in_binary,address):
    for oct in octets:
        address_in_binary.append(str(int(oct,2)))
        address = ".".join(address_in_binary)
    return address
def rand_ip_gen():
     while True:
            generate = input("Generate random IP address from this subnet? (y/n)")
            if generate == "y":
                generated_ip = []

                for i in range (0,4):
                    if bst_ip_address[i] == net_ip_address[i]:
                        generated_ip.append(bst_ip_address[i])
                    else:
                        generated_ip.append(str(random.randint(int(net_ip_address[i])+1, int(bst_ip_address[i])-1)))

                y_iaddr = ".".join(generated_ip)
                print("Random IP address is: %s" % y_iaddr)
                print("\n")
                continue
                
            else:
                print("Ok, bye!\n")
                break
				


def subnet_calc():
    try:
        print("\n")
        while True:
            ip_address = input("Enter an IP address: ")
            ip_octets = ip_address.split('.')         
            if (len(ip_octets) == 4) and (1 <= int(ip_octets[0]) <= 223) and (int(ip_octets[0]) != 127) and (int(ip_octets[0]) != 169 or int(ip_octets[1]) != 254) and (0 <= int(ip_octets[1]) <= 255 and 0 <= int(ip_octets[2]) <= 255 and 0 <= int(ip_octets[3]) <= 255):
                break
            else:
                print("\nThe IP address is INVALID! Please retry!\n")
                continue
    
        masks = [255, 254, 252, 248, 240, 224, 192, 128, 0]
        
        while True:
            subnet_mask = input("Enter a subnet mask: ")
   
            mask_octets = subnet_mask.split('.')
            
            if (len(mask_octets) == 4) and (int(mask_octets[0]) == 255) and (int(mask_octets[1]) in masks) and (int(mask_octets[2]) in masks) and (int(mask_octets[3]) in masks) and (int(mask_octets[0]) >= int(mask_octets[1]) >= int(mask_octets[2]) >= int(mask_octets[3])):
                break    
            else:
                print("\nThe subnet mask is INVALID! Please retry!\n")
                continue

        mask_octets_binary = []
        
        convert_binary(mask_octets,mask_octets_binary)

        binary_mask = "".join(mask_octets_binary)
        no_of_zeros = binary_mask.count("0")
        no_of_ones = 32 - no_of_zeros
        no_of_hosts = abs(2 ** no_of_zeros - 2) 

        wildcard_octets = []
        
        for octet in mask_octets:
            wild_octet = 255 - int(octet)
            wildcard_octets.append(str(wild_octet))
            

        wildcard_mask = ".".join(wildcard_octets)

        ip_octets_binary = []
        convert_binary(ip_octets,ip_octets_binary)

        binary_ip = "".join(ip_octets_binary)
    
        network_address_binary = binary_ip[:(no_of_ones)] + "0" * no_of_zeros
        broadcast_address_binary = binary_ip[:(no_of_ones)] + "1" * no_of_zeros
        net_ip_octets = []
        bst_ip_octets = []

        for bit in range(0, 32, 8):
            net_ip_octet = network_address_binary[bit: bit + 8]
            net_ip_octets.append(net_ip_octet)
            bst_ip_octet = broadcast_address_binary[bit: bit + 8]
            bst_ip_octets.append(bst_ip_octet)
    
        net_ip_address = []
        bst_ip_address = []
        network_address = ""
        broadcast_address = ""
        convert_address(net_ip_octets,net_ip_address,network_address)
        convert_address(bst_ip_octets,bst_ip_address,broadcast_address)
      
        print("\n")
        print("Network address is: %s" % network_address)
        print("Broadcast address is: %s" % broadcast_address)
        print("Number of valid hosts per subnet: %s" % no_of_hosts)
        print("Wildcard mask: %s" % wildcard_mask)
        print("Mask bits: %s" % no_of_ones)
        print("\n")

        rand_ip_gen()
		
    except KeyboardInterrupt:
        print("\n\nExiting...\n")
        sys.exit()
        
		
subnet_calc()