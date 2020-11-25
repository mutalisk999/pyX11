#include "x11.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "sph_blake.h"
#include "sph_bmw.h"
#include "sph_groestl.h"
#include "sph_jh.h"
#include "sph_keccak.h"
#include "sph_skein.h"
#include "sph_luffa.h"
#include "sph_cubehash.h"
#include "sph_shavite.h"
#include "sph_simd.h"
#include "sph_echo.h"


void x11_hash(const char* input, char* output, uint32_t len)
{
    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;

    sph_luffa512_context		ctx_luffa1;
    sph_cubehash512_context		ctx_cubehash1;
    sph_shavite512_context		ctx_shavite1;
    sph_simd512_context		ctx_simd1;
    sph_echo512_context		ctx_echo1;

    //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, input, len);
    sph_blake512_close (&ctx_blake, hashA);

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, hashA, 64);
    sph_bmw512_close(&ctx_bmw, hashB);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, hashB, 64);
    sph_groestl512_close(&ctx_groestl, hashA);

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, hashA, 64);
    sph_skein512_close (&ctx_skein, hashB);

    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, hashB, 64);
    sph_jh512_close(&ctx_jh, hashA);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashA, 64);
    sph_keccak512_close(&ctx_keccak, hashB);

    sph_luffa512_init (&ctx_luffa1);
    sph_luffa512 (&ctx_luffa1, hashB, 64);
    sph_luffa512_close (&ctx_luffa1, hashA);

    sph_cubehash512_init (&ctx_cubehash1);
    sph_cubehash512 (&ctx_cubehash1, hashA, 64);
    sph_cubehash512_close(&ctx_cubehash1, hashB);

    sph_shavite512_init (&ctx_shavite1);
    sph_shavite512 (&ctx_shavite1, hashB, 64);
    sph_shavite512_close(&ctx_shavite1, hashA);

    sph_simd512_init (&ctx_simd1);
    sph_simd512 (&ctx_simd1, hashA, 64);
    sph_simd512_close(&ctx_simd1, hashB);

    sph_echo512_init (&ctx_echo1);
    sph_echo512 (&ctx_echo1, hashB, 64);
    sph_echo512_close(&ctx_echo1, hashA);

    memcpy(output, hashA, 32);
}

/*
int main() {
	//51b572209083576ea221c27e62b4e22063257571ccb6cc3dc3cd17eb67584eba
	char *in1 = "";
	char o1[32];
	char *out1 = o1;
	x11_hash(in1, out1, strlen(in1));
	for(int i = 0; i < 32; ++i)
		printf("%02x", (unsigned char)o1[i]);
	printf("\n");
	
	//534536a4e4f16b32447f02f77200449dc2f23b532e3d9878fe111c9de666bc5c
	char *in2 = "The quick brown fox jumps over the lazy dog";
	char o2[32];
	char *out2 = o2;
	x11_hash(in2, out2, strlen(in2));
	for(int i = 0; i < 32; ++i) 
		printf("%02x", (unsigned char)o2[i]);
	printf("\n");
	
	//fe809ebca8753d907f6ad32cdcf8e5c4e090d7bece5df35b2147e10b88c12d26
	char *in3 = "DASH";
	char o3[32];
	char *out3 = o3;
	x11_hash(in3, out3, strlen(in3));
	for(int i = 0; i < 32; ++i) 
		printf("%02x", (unsigned char)o3[i]);
	printf("\n");
	
	//5c0996b9d49dbe84e29f1b818c1fa9e73549f894a71b8a258964b8f0ecf3c866
	char *in4 = "Take this kiss upon the brow! And, in parting from you now, Thus much let me avow-- You are not wrong, who deem That my days have been a dream; Yet if hope has flown away In a night, or in a day, In a vision, or in none, Is it therefore the less gone? All that we see or seem Is but a dream within a dream. I stand amid the roar Of a surf-tormented shore, And I hold within my hand Grains of the golden sand-- How few! yet how they creep Through my fingers to the deep, While I weep--while I weep! O God! can I not grasp Them with a tighter clasp? O God! can I not save One from the pitiless wave? Is all that we see or seem But a dream within a dream?";
	char o4[32];
	char *out4 = o4;
	x11_hash(in4, out4, strlen(in4));
	for(int i = 0; i < 32; ++i) 
		printf("%02x", (unsigned char)o4[i]);
	printf("\n");
	
	return 0;
}
*/
