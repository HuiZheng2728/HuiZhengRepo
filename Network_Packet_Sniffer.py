import logging
from datetime import datetime
import subprocess
import sys

logging.getLogger("scapy.runtime").setLevel(logging.ERROR)
logging.getLogger("scapy.interactive").setLevel(logging.ERROR)
logging.getLogger("scapy.loading").setLevel(logging.ERROR)

try:
	from scapy.all import*
	
except ImportError:
	print("Scapy for python is not installed")
	sys.exit()

try:
	subprocess.call(["ifconfig",net_iface,"promisc"],stdout=None,stderr = None,shell = False)
except:
	print("failed to configure interface as promiscuous")
else:
	print(f"Interface {net_iface} on promisc mode")

pkt_to_sniff = input("Enter the number of packets to capture: ")
if int(pkt_to_sniff) != 0 :
	print(f"The program will capture {pkt_to_sniff} packets")
else:
	print("The program will capture packets untill the time expires.")


time_to_sniff = input("Enter the number of seconds to run the capture: ")
print(" starting ")
if int(time_to_sniff)!=0:
	print(f"The program will run for {time_to_sniff} seconds")

proto_sniff = input(" Enter the protocol to filter by (arp|bootp|icmp|0 is all): ")
if (proto_sniff == "arp") or (proto_sniff == "bootp") or (proto_sniff == "icmp"):
	print("\nThe program will capture only %s packets.\n" % proto_sniff.upper())
elif (proto_sniff) == "0":
	print("\nThe program will capture all protocols.\n")
	

	
file_name = input (" Enter name of the log file")
sniffer_log = open(file_name,"a")


def packet_log(packet):
	time_now=datetime.now()
	if proto_sniff == "0":
		print("Time: " + str(time_now) + " Protocol: ALL"+ "SMAC: " + packet[0].src + " DMAC: "+ packet[0].dest,file = sniffer_log)
	elif (proto_sniff == "arp") or (proto_sniff == "bootp") or (proto_sniff == "icmp"):
		print("Time: " + str(now) + " Protocol: " + proto_sniff.upper() + " SMAC: " + packet[0].src + " DMAC: " + packet[0].dst, file = sniffer_log)
