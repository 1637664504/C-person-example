#include <netinet/in.h>
#include <net/if.h>

//netinet/in.h
//#define IPPROTO_UDP 0x11

#define ETH_HEAD_LEN 14

typedef struct _ethhdr
{
    unsigned char dst_mac[IFHWADDRLEN];
    unsigned char src_mac[IFHWADDRLEN];
    unsigned short type;
}__attribute__((packed)) ethhdr_t;

typedef struct _iphdr
{     
    unsigned char h_verlen;
    unsigned char tos;
    unsigned short total_len;
    unsigned short ident; 
    unsigned short frag_and_flags;
    unsigned char ttl;
    unsigned char protocol; 
    unsigned short checksum; 
    unsigned int src_ip;   
    unsigned int dst_ip; 
}__attribute__((packed)) iphdr_t;  

typedef struct _udphdr 
{
    unsigned short sport; 
    unsigned short dport;
    unsigned short len;  
    unsigned short sum;
}__attribute__((packed)) udphdr_t;