#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "def.h"

#define MAX    512      // 1~2,2~4をそれぞれ512分割、計1024分割
#define MASK9  8372224  // ((1 << 9) - 1) << 14
#define MASK10 8380416  // ((1 << 10) - 1) << 13 
#define MASK14 16383    // 11111111111111


static long long unsigned int make_l[MAX*2];

uint32_t fsqrt(uint32_t a_uint32) {
  
  union data_32bit a, x, result;
  
  a.uint32 = a_uint32;

  if (a.sign == 1) {
    if (a.exp == 0) {
      result.uint32 = NZERO;
    } else {
      result.uint32 = NNAN;
    }
  } else if (a.exp == 0) {
    result.uint32 = ZERO;
  } else if (a.exp == 255 && a.frac != 0) {
    result.uint32 = MY_NAN;
  } else if (a.uint32 == INF) {
    result.uint32 = INF;
  } else {
    
    int index;
    unsigned int exp, y, d, n;
    long long unsigned int l;

    result.sign = 0;
    x.uint32 = a.uint32;

    index = (x.frac & MASK9) >> 14;
    
    if ((x.exp & 1) == 0) {      // 2の奇数乗の場合 ※exp-127
      index += (1 << 9);
    } else {
      // 何もしない
    }
    
    if (a.exp >= 127) {
      exp = a.exp - 127;
      exp = exp >> 1;
      result.exp = 127 + exp;
    } else {
      exp = 127 - a.exp;
      exp = (exp + 1) >> 1;
      result.exp = 127 - exp;
    }   

    l = make_l[index];
    y = l >> 13;
    if ((x.exp & 1) == 0) {
      d = (1 << 13) + (l & 0x1fff);
    } else {
      d = l & 0x1fff;
    }
    n = a.frac & MASK14;

    result.frac = y + ((d * n) >> 14);

  }
  return (result.uint32);
}

static long long unsigned int make_l[MAX*2] = {
  0x000001ffd,
  0x003ffbff4,
  0x007fe3fec,
  0x00bfbbfe4,
  0x00ff83fdc,
  0x013f3bfd4,
  0x017ee3fcd,
  0x01be7dfc4,
  0x01fe05fbd,
  0x023d7ffb5,
  0x027ce9fae,
  0x02bc45fa5,
  0x02fb8ff9e,
  0x033acbf96,
  0x0379f7f8e,
  0x03b913f87,
  0x03f821f7f,
  0x04371ff78,
  0x04760ff70,
  0x04b4eff68,
  0x04f3bff61,
  0x053281f59,
  0x057133f52,
  0x05afd7f4a,
  0x05ee6bf43,
  0x062cf1f3b,
  0x066b67f34,
  0x06a9cff2c,
  0x06e827f25,
  0x072671f1e,
  0x0764adf17,
  0x07a2dbf0f,
  0x07e0f9f07,
  0x081f07f01,
  0x085d09ef9,
  0x089afbef2,
  0x08d8dfeeb,
  0x0916b5ee3,
  0x09547bedd,
  0x099235ed5,
  0x09cfdfece,
  0x0a0d7bec7,
  0x0a4b09ec0,
  0x0a8889eb8,
  0x0ac5f9eb2,
  0x0b035deab,
  0x0b40b3ea3,
  0x0b7df9e9d,
  0x0bbb33e95,
  0x0bf85de8f,
  0x0c357be87,
  0x0c7289e81,
  0x0caf8be7a,
  0x0cec7fe73,
  0x0d2965e6c,
  0x0d663de65,
  0x0da307e5e,
  0x0ddfc3e58,
  0x0e1c73e50,
  0x0e5913e4a,
  0x0e95a7e43,
  0x0ed22de3c,
  0x0f0ea5e36,
  0x0f4b11e2f,
  0x0f876fe28,
  0x0fc3bfe21,
  0x100001e1b,
  0x103c37e14,
  0x10785fe0e,
  0x10b47be07,
  0x10f089e00,
  0x112c89dfa,
  0x11687ddf3,
  0x11a463dec,
  0x11e03bde6,
  0x121c07de0,
  0x1257c7dd9,
  0x129379dd3,
  0x12cf1fdcc,
  0x130ab7dc5,
  0x134641dbf,
  0x1381bfdb9,
  0x13bd31db3,
  0x13f897dac,
  0x1433efda5,
  0x146f39d9f,
  0x14aa77d99,
  0x14e5a9d93,
  0x1520cfd8c,
  0x155be7d86,
  0x1596f3d80,
  0x15d1f3d79,
  0x160ce5d74,
  0x1647cdd6d,
  0x1682a7d66,
  0x16bd73d61,
  0x16f835d5a,
  0x1732e9d55,
  0x176d93d4e,
  0x17a82fd48,
  0x17e2bfd42,
  0x181d43d3b,
  0x1857b9d36,
  0x189225d2f,
  0x18cc83d2a,
  0x1906d7d23,
  0x19411dd1e,
  0x197b59d17,
  0x19b587d12,
  0x19efabd0b,
  0x1a29c1d05,
  0x1a63cbd00,
  0x1a9dcbcf9,
  0x1ad7bdcf4,
  0x1b11a5cee,
  0x1b4b81ce7,
  0x1b854fce2,
  0x1bbf13cdc,
  0x1bf8cbcd6,
  0x1c3277cd1,
  0x1c6c19cca,
  0x1ca5adcc5,
  0x1cdf37cbf,
  0x1d18b5cb9,
  0x1d5227cb3,
  0x1d8b8dcad,
  0x1dc4e7ca8,
  0x1dfe37ca2,
  0x1e377bc9d,
  0x1e70b5c96,
  0x1ea9e1c91,
  0x1ee303c8b,
  0x1f1c19c86,
  0x1f5525c80,
  0x1f8e25c7a,
  0x1fc719c74,
  0x200001c6f,
  0x2038dfc6a,
  0x2071b3c63,
  0x20aa79c5f,
  0x20e337c58,
  0x211be7c53,
  0x21548dc4e,
  0x218d29c48,
  0x21c5b9c42,
  0x21fe3dc3d,
  0x2236b7c38,
  0x226f27c32,
  0x22a78bc2c,
  0x22dfe3c27,
  0x231831c22,
  0x235075c1c,
  0x2388adc17,
  0x23c0dbc12,
  0x23f8ffc0c,
  0x243117c06,
  0x246923c01,
  0x24a125bfc,
  0x24d91dbf7,
  0x25110bbf1,
  0x2548edbec,
  0x2580c5be7,
  0x25b893be1,
  0x25f055bdc,
  0x26280dbd7,
  0x265fbbbd1,
  0x26975dbcc,
  0x26cef5bc7,
  0x270683bc2,
  0x273e07bbd,
  0x277581bb7,
  0x27acefbb2,
  0x27e453bad,
  0x281badba8,
  0x2852fdba3,
  0x288a43b9d,
  0x28c17db98,
  0x28f8adb94,
  0x292fd5b8e,
  0x2966f1b89,
  0x299e03b84,
  0x29d50bb7f,
  0x2a0c09b79,
  0x2a42fbb75,
  0x2a79e5b70,
  0x2ab0c5b6a,
  0x2ae799b66,
  0x2b1e65b61,
  0x2b5527b5b,
  0x2b8bddb57,
  0x2bc28bb51,
  0x2bf92db4d,
  0x2c2fc7b48,
  0x2c6657b43,
  0x2c9cddb3d,
  0x2cd357b39,
  0x2d09c9b34,
  0x2d4031b2f,
  0x2d768fb2a,
  0x2dace3b26,
  0x2de32fb20,
  0x2e196fb1b,
  0x2e4fa5b17,
  0x2e85d3b12,
  0x2ebbf7b0d,
  0x2ef211b08,
  0x2f2821b03,
  0x2f5e27aff,
  0x2f9425af9,
  0x2fca17af5,
  0x300001af0,
  0x3035e1aec,
  0x306bb9ae6,
  0x30a185ae2,
  0x30d749add,
  0x310d03ad9,
  0x3142b5ad3,
  0x31785bacf,
  0x31adf9acb,
  0x31e38fac5,
  0x321919ac1,
  0x324e9babc,
  0x328413ab8,
  0x32b983ab3,
  0x32eee9aae,
  0x332445aaa,
  0x335999aa5,
  0x338ee3aa0,
  0x33c423a9c,
  0x33f95ba97,
  0x342e89a93,
  0x3463afa8e,
  0x3498cba8a,
  0x34cddfa84,
  0x3502e7a81,
  0x3537e9a7c,
  0x356ce1a77,
  0x35a1cfa73,
  0x35d6b5a6e,
  0x360b91a6a,
  0x364065a65,
  0x36752fa61,
  0x36a9f1a5c,
  0x36dea9a58,
  0x371359a53,
  0x3747ffa4f,
  0x377c9da4b,
  0x37b133a46,
  0x37e5bfa42,
  0x381a43a3d,
  0x384ebda39,
  0x38832fa34,
  0x38b797a30,
  0x38ebf7a2c,
  0x39204fa27,
  0x39549da23,
  0x3988e3a1e,
  0x39bd1fa1b,
  0x39f155a16,
  0x3a2581a11,
  0x3a59a3a0d,
  0x3a8dbda09,
  0x3ac1cfa05,
  0x3af5d9a00,
  0x3b29d99fc,
  0x3b5dd19f8,
  0x3b91c19f3,
  0x3bc5a79f0,
  0x3bf9879eb,
  0x3c2d5d9e6,
  0x3c61299e3,
  0x3c94ef9de,
  0x3cc8ab9da,
  0x3cfc5f9d6,
  0x3d300b9d2,
  0x3d63af9cd,
  0x3d97499c9,
  0x3dcadb9c5,
  0x3dfe659c1,
  0x3e31e79bd,
  0x3e65619b8,
  0x3e98d19b5,
  0x3ecc3b9b0,
  0x3eff9b9ac,
  0x3f32f39a8,
  0x3f66439a4,
  0x3f998b9a0,
  0x3fcccb99b,
  0x400001998,
  0x403331993,
  0x406657990,
  0x40997798b,
  0x40cc8d987,
  0x40ff9b983,
  0x4132a1980,
  0x4165a197b,
  0x419897977,
  0x41cb85973,
  0x41fe6b96f,
  0x42314996b,
  0x42641f967,
  0x4296ed963,
  0x42c9b395f,
  0x42fc7195b,
  0x432f27957,
  0x4361d5953,
  0x43947b94f,
  0x43c71994b,
  0x43f9af947,
  0x442c3d944,
  0x445ec593f,
  0x44914393b,
  0x44c3b9938,
  0x44f629933,
  0x45288f930,
  0x455aef92c,
  0x458d47928,
  0x45bf97924,
  0x45f1df920,
  0x46241f91c,
  0x465657919,
  0x468889914,
  0x46bab1911,
  0x46ecd390d,
  0x471eed909,
  0x4750ff905,
  0x478309901,
  0x47b50b8fe,
  0x47e7078fa,
  0x4818fb8f6,
  0x484ae78f2,
  0x487ccb8ee,
  0x48aea78eb,
  0x48e07d8e7,
  0x49124b8e3,
  0x4944118df,
  0x4975cf8db,
  0x49a7858d8,
  0x49d9358d4,
  0x4a0add8d1,
  0x4a3c7f8cc,
  0x4a6e178c9,
  0x4a9fa98c5,
  0x4ad1338c2,
  0x4b02b78bd,
  0x4b34318bb,
  0x4b65a78b6,
  0x4b97138b3,
  0x4bc8798af,
  0x4bf9d78ab,
  0x4c2b2d8a8,
  0x4c5c7d8a4,
  0x4c8dc58a0,
  0x4cbf0589d,
  0x4cf03f899,
  0x4d2171895,
  0x4d529b892,
  0x4d83bf88e,
  0x4db4db88b,
  0x4de5f1887,
  0x4e16ff883,
  0x4e4805880,
  0x4e790587d,
  0x4ea9ff878,
  0x4edaef875,
  0x4f0bd9872,
  0x4f3cbd86e,
  0x4f6d9986a,
  0x4f9e6d867,
  0x4fcf3b863,
  0x500001860,
  0x5030c185c,
  0x506179859,
  0x50922b855,
  0x50c2d5852,
  0x50f37984e,
  0x51241584b,
  0x5154ab847,
  0x518539843,
  0x51b5bf841,
  0x51e64183c,
  0x5216b9839,
  0x52472b836,
  0x527797833,
  0x52a7fd82e,
  0x52d85982c,
  0x5308b1828,
  0x533901824,
  0x536949821,
  0x53998b81e,
  0x53c9c781a,
  0x53f9fb817,
  0x542a29813,
  0x545a4f810,
  0x548a6f80d,
  0x54ba89809,
  0x54ea9b806,
  0x551aa7802,
  0x554aab800,
  0x557aab7fb,
  0x55aaa17f9,
  0x55da937f5,
  0x560a7d7f1,
  0x563a5f7ee,
  0x566a3b7eb,
  0x569a117e8,
  0x56c9e17e4,
  0x56f9a97e1,
  0x57296b7de,
  0x5759277da,
  0x5788db7d7,
  0x57b8897d4,
  0x57e8317d0,
  0x5817d17cd,
  0x58476b7ca,
  0x5876ff7c6,
  0x58a68b7c4,
  0x58d6137c0,
  0x5905937bc,
  0x59350b7ba,
  0x59647f7b6,
  0x5993eb7b3,
  0x59c3517af,
  0x59f2af7ad,
  0x5a22097a9,
  0x5a515b7a6,
  0x5a80a77a3,
  0x5aafed79f,
  0x5adf2b79c,
  0x5b0e6379a,
  0x5b3d97795,
  0x5b6cc1793,
  0x5b9be7790,
  0x5bcb0778c,
  0x5bfa1f789,
  0x5c2931786,
  0x5c583d783,
  0x5c874377f,
  0x5cb64177d,
  0x5ce53b779,
  0x5d142d776,
  0x5d4319773,
  0x5d71ff770,
  0x5da0df76c,
  0x5dcfb776a,
  0x5dfe8b766,
  0x5e2d57764,
  0x5e5c1f760,
  0x5e8adf75d,
  0x5eb99975a,
  0x5ee84d757,
  0x5f16fb753,
  0x5f45a1751,
  0x5f744374d,
  0x5fa2dd74b,
  0x5fd173747,
  0x600001744,
  0x602e89742,
  0x605d0d73e,
  0x608b8973b,
  0x60b9ff738,
  0x60e86f735,
  0x6116d9732,
  0x61453d72f,
  0x61739b72b,
  0x61a1f1729,
  0x61d043726,
  0x61fe8f723,
  0x622cd5720,
  0x625b1571c,
  0x62894d71a,
  0x62b781717,
  0x62e5af713,
  0x6313d5711,
  0x6341f770e,
  0x63701370a,
  0x639e27708,
  0x63cc37705,
  0x63fa41702,
  0x6428456fe,
  0x6456416fc,
  0x6484396f9,
  0x64b22b6f6,
  0x64e0176f3,
  0x650dfd6f0,
  0x653bdd6ed,
  0x6569b76ea,
  0x65978b6e7,
  0x65c5596e5,
  0x65f3236e1,
  0x6620e56de,
  0x664ea16dc,
  0x667c596d8,
  0x66aa096d6,
  0x66d7b56d3,
  0x67055b6d0,
  0x6732fb6cd,
  0x6760956ca,
  0x678e296c7,
  0x67bbb76c4,
  0x67e93f6c2,
  0x6816c36be,
  0x68443f6bc,
  0x6871b76b9,
  0x689f296b6,
  0x68cc956b3,
  0x68f9fb6b0,
  0x69275b6ad,
  0x6954b56ab,
  0x69820b6a7,
  0x69af596a5,
  0x69dca36a2,
  0x6a09e8d3b,
  0x6a645ed31,
  0x6abec0d25,
  0x6b190ad1a,
  0x6b733ed0e,
  0x6bcd5ad04,
  0x6c2762cf8,
  0x6c8152cee,
  0x6cdb2ece2,
  0x6d34f2cd7,
  0x6d8ea0ccc,
  0x6de838cc2,
  0x6e41bccb6,
  0x6e9b28cab,
  0x6ef47eca1,
  0x6f4dc0c96,
  0x6fa6ecc8b,
  0x700002c80,
  0x705902c75,
  0x70b1ecc6b,
  0x710ac2c60,
  0x716382c55,
  0x71bc2cc4b,
  0x7214c2c40,
  0x726d42c36,
  0x72c5aec2b,
  0x731e04c21,
  0x737646c16,
  0x73ce72c0b,
  0x742688c02,
  0x747e8cbf7,
  0x74d67abec,
  0x752e52be2,
  0x758616bd8,
  0x75ddc6bce,
  0x763562bc3,
  0x768ce8bb9,
  0x76e45abaf,
  0x773bb8ba5,
  0x779302b9b,
  0x77ea38b90,
  0x784158b87,
  0x789866b7c,
  0x78ef5eb72,
  0x794642b69,
  0x799d14b5e,
  0x79f3d0b55,
  0x7a4a7ab4a,
  0x7aa10eb41,
  0x7af790b37,
  0x7b4dfeb2d,
  0x7ba458b23,
  0x7bfa9eb19,
  0x7c50d0b10,
  0x7ca6f0b06,
  0x7cfcfcafc,
  0x7d52f4af2,
  0x7da8d8ae9,
  0x7dfeaaadf,
  0x7e5468ad6,
  0x7eaa14acc,
  0x7effacac2,
  0x7f5530ab9,
  0x7faaa2ab0,
  0x800002aa6,
  0x80554ea9c,
  0x80aa86a93,
  0x80ffaca8a,
  0x8154c0a80,
  0x81a9c0a77,
  0x81feaea6d,
  0x825388a65,
  0x82a852a5b,
  0x82fd08a51,
  0x8351aaa49,
  0x83a63ca3f,
  0x83fabaa36,
  0x844f26a2d,
  0x84a380a24,
  0x84f7c8a1a,
  0x854bfca12,
  0x85a020a08,
  0x85f4309ff,
  0x86482e9f7,
  0x869c1c9ed,
  0x86eff69e5,
  0x8743c09db,
  0x8797769d2,
  0x87eb1a9ca,
  0x883eae9c0,
  0x88922e9b8,
  0x88e59e9af,
  0x8938fc9a6,
  0x898c4899e,
  0x89df84994,
  0x8a32ac98c,
  0x8a85c4983,
  0x8ad8ca97a,
  0x8b2bbe971,
  0x8b7ea0969,
  0x8bd172961,
  0x8c2434957,
  0x8c76e294f,
  0x8cc980946,
  0x8d1c0c93e,
  0x8d6e88936,
  0x8dc0f492c,
  0x8e134c924,
  0x8e659491c,
  0x8eb7cc913,
  0x8f09f290b,
  0x8f5c08903,
  0x8fae0e8fa,
  0x9000028f1,
  0x9051e48e9,
  0x90a3b68e1,
  0x90f5788d9,
  0x91472a8d0,
  0x9198ca8c8,
  0x91ea5a8bf,
  0x923bd88b8,
  0x928d488af,
  0x92dea68a7,
  0x932ff489f,
  0x938132896,
  0x93d25e88f,
  0x94237c886,
  0x94748887e,
  0x94c584876,
  0x95167086e,
  0x95674c866,
  0x95b81885e,
  0x9608d4856,
  0x96598084e,
  0x96aa1c846,
  0x96faa883e,
  0x974b24836,
  0x979b9082e,
  0x97ebec826,
  0x983c3881f,
  0x988c76816,
  0x98dca280f,
  0x992cc0806,
  0x997ccc7ff,
  0x99ccca7f7,
  0x9a1cb87f0,
  0x9a6c987e7,
  0x9abc667e0,
  0x9b0c267d8,
  0x9b5bd67d1,
  0x9bab787c8,
  0x9bfb087c1,
  0x9c4a8a7ba,
  0x9c99fe7b1,
  0x9ce9607aa,
  0x9d38b47a3,
  0x9d87fa79b,
  0x9dd730793,
  0x9e265678c,
  0x9e756e784,
  0x9ec47677c,
  0x9f136e776,
  0x9f625a76d,
  0x9fb134766,
  0xa0000075f,
  0xa04ebe757,
  0xa09d6c750,
  0xa0ec0c749,
  0xa13a9e741,
  0xa1892073a,
  0xa1d794732,
  0xa225f872b,
  0xa2744e724,
  0xa2c29671c,
  0xa310ce715,
  0xa35ef870e,
  0xa3ad14706,
  0xa3fb20700,
  0xa449206f8,
  0xa497106f0,
  0xa4e4f06ea,
  0xa532c46e2,
  0xa580886dc,
  0xa5ce406d4,
  0xa61be86cd,
  0xa669826c6,
  0xa6b70e6be,
  0xa7048a6b8,
  0xa751fa6b1,
  0xa79f5c6a9,
  0xa7ecae6a3,
  0xa839f469b,
  0xa8872a694,
  0xa8d45268e,
  0xa9216e686,
  0xa96e7a680,
  0xa9bb7a678,
  0xaa086a672,
  0xaa554e66a,
  0xaaa222664,
  0xaaeeea65d,
  0xab3ba4656,
  0xab885064f,
  0xabd4ee648,
  0xac217e642,
  0xac6e0263a,
  0xacba76634,
  0xad06de62d,
  0xad5338626,
  0xad9f8461f,
  0xadebc2619,
  0xae37f4612,
  0xae841860b,
  0xaed02e604,
  0xaf1c365fe,
  0xaf68325f7,
  0xafb4205f0,
  0xb000005ea,
  0xb04bd45e3,
  0xb0979a5dd,
  0xb0e3545d5,
  0xb12efe5d0,
  0xb17a9e5c8,
  0xb1c62e5c2,
  0xb211b25bc,
  0xb25d2a5b5,
  0xb2a8945ae,
  0xb2f3f05a8,
  0xb33f405a1,
  0xb38a8259b,
  0xb3d5b8595,
  0xb420e258d,
  0xb46bfc588,
  0xb4b70c581,
  0xb5020e57a,
  0xb54d02575,
  0xb597ec56d,
  0xb5e2c6568,
  0xb62d96561,
  0xb6785855a,
  0xb6c30c554,
  0xb70db454e,
  0xb75850548,
  0xb7a2e0541,
  0xb7ed6253b,
  0xb837d8535,
  0xb8824252e,
  0xb8cc9e528,
  0xb916ee522,
  0xb9613251c,
  0xb9ab6a515,
  0xb9f59450f,
  0xba3fb2509,
  0xba89c4503,
  0xbad3ca4fc,
  0xbb1dc24f7,
  0xbb67b04f0,
  0xbbb1904ea,
  0xbbfb644e4,
  0xbc452c4de,
  0xbc8ee84d7,
  0xbcd8964d2,
  0xbd223a4cc,
  0xbd6bd24c5,
  0xbdb55c4bf,
  0xbdfeda4ba,
  0xbe484e4b3,
  0xbe91b44ad,
  0xbedb0e4a8,
  0xbf245e4a1,
  0xbf6da049b,
  0xbfb6d6495,
  0xc00000490,
  0xc04920489,
  0xc09232483,
  0xc0db3847e,
  0xc12434477,
  0xc16d22472,
  0xc1b60646c,
  0xc1fede466,
  0xc247aa45f,
  0xc2906845b,
  0xc2d91e454,
  0xc321c644e,
  0xc36a62449,
  0xc3b2f4442,
  0xc3fb7843d,
  0xc443f2437,
  0xc48c60432,
  0xc4d4c442b,
  0xc51d1a426,
  0xc56566420,
  0xc5ada641a,
  0xc5f5da415,
  0xc63e0440e,
  0xc68620409,
  0xc6ce32404,
  0xc7163a3fd,
  0xc75e343f8,
  0xc7a6243f3,
  0xc7ee0a3ec,
  0xc835e23e7,
  0xc87db03e2,
  0xc8c5743db,
  0xc90d2a3d6,
  0xc954d63d1,
  0xc99c783cb,
  0xc9e40e3c5,
  0xca2b983c0,
  0xca73183ba,
  0xcaba8c3b4,
  0xcb01f43af,
  0xcb49523aa,
  0xcb90a63a4,
  0xcbd7ee39e,
  0xcc1f2a399,
  0xcc665c393,
  0xccad8238e,
  0xccf49e389,
  0xcd3bb0382,
  0xcd82b437e,
  0xcdc9b0378,
  0xce10a0373,
  0xce578636d,
  0xce9e60367,
  0xcee52e363,
  0xcf2bf435d,
  0xcf72ae357,
  0xcfb95c352,
  0xd0000034d,
  0xd0469a347,
  0xd08d28343,
  0xd0d3ae33c,
  0xd11a26338,
  0xd16096332,
  0xd1a6fa32c,
  0xd1ed52328,
  0xd233a2322,
  0xd279e631d,
  0xd2c020317,
  0xd3064e313,
  0xd34c7230e,
  0xd3928e307,
  0xd3d89c303,
  0xd41ea22fd,
  0xd4649c2f8,
  0xd4aa8c2f3,
  0xd4f0722ee,
  0xd5364e2e8,
  0xd57c1e2e3,
  0xd5c1e42de,
  0xd607a02d9,
  0xd64d522d4,
  0xd692fa2cf,
  0xd6d8982c9,
  0xd71e2a2c4,
  0xd763b22c0,
  0xd7a9322ba,
  0xd7eea62b5,
  0xd834102af,
  0xd8796e2ab,
  0xd8bec42a6,
  0xd904102a1,
  0xd9495229b,
  0xd98e88297,
  0xd9d3b6291,
  0xda18d828c,
  0xda5df0288,
  0xdaa300282,
  0xdae80427e,
  0xdb2d00278,
  0xdb71f0273,
  0xdbb6d626f,
  0xdbfbb4269,
  0xdc4086264,
  0xdc854e260,
  0xdcca0e25a,
  0xdd0ec2256,
  0xdd536e251,
  0xdd981024b,
  0xdddca6247,
  0xde2134242,
  0xde65b823d,
  0xdeaa32238,
  0xdeeea2233,
  0xdf330822e,
  0xdf776422a,
  0xdfbbb8224,
  0xe00000220,
  0xe0444021b,
  0xe08876216,
  0xe0cca2211,
  0xe110c420c,
  0xe154dc208,
  0xe198ec203,
  0xe1dcf21fe,
  0xe220ee1f9,
  0xe264e01f4,
  0xe2a8c81f0,
  0xe2eca81eb,
  0xe3307e1e6,
  0xe3744a1e1,
  0xe3b80c1dd,
  0xe3fbc61d8,
  0xe43f761d3,
  0xe4831c1ce,
  0xe4c6b81ca,
  0xe50a4c1c5,
  0xe54dd61c0,
  0xe591561bc,
  0xe5d4ce1b6,
  0xe6183a1b3,
  0xe65ba01ad,
  0xe69efa1a9,
  0xe6e24c1a4,
  0xe725941a0,
  0xe768d419b,
  0xe7ac0a196,
  0xe7ef36192,
  0xe8325a18d,
  0xe87574189,
  0xe8b886184,
  0xe8fb8e17f,
  0xe93e8c17b,
  0xe98182176,
  0xe9c46e171,
  0xea075016e,
  0xea4a2c168,
  0xea8cfc164,
  0xeacfc415f,
  0xeb128215b,
  0xeb5538156,
  0xeb97e4152,
  0xebda8814e,
  0xec1d24148,
  0xec5fb4145,
  0xeca23e13f,
  0xece4bc13c,
  0xed2734137,
  0xed69a2132,
  0xedac0612e,
  0xedee62129,
  0xee30b4125,
  0xee72fe121,
  0xeeb54011c,
  0xeef778118,
  0xef39a8113,
  0xef7bce10f,
  0xefbdec10a,
  0xf00000106,
  0xf0420c102,
  0xf084100fd,
  0xf0c60a0f9,
  0xf107fc0f5,
  0xf149e60f0,
  0xf18bc60ec,
  0xf1cd9e0e7,
  0xf20f6c0e3,
  0xf251320df,
  0xf292f00da,
  0xf2d4a40d7,
  0xf316520d1,
  0xf357f40ce,
  0xf399900c9,
  0xf3db220c5,
  0xf41cac0c0,
  0xf45e2c0bd,
  0xf49fa60b8,
  0xf4e1160b4,
  0xf5227e0af,
  0xf563dc0ab,
  0xf5a5320a7,
  0xf5e6800a3,
  0xf627c609e,
  0xf6690209b,
  0xf6aa38096,
  0xf6eb64091,
  0xf72c8608e,
  0xf76da2089,
  0xf7aeb4086,
  0xf7efc0081,
  0xf830c207c,
  0xf871ba079,
  0xf8b2ac074,
  0xf8f394071,
  0xf9347606c,
  0xf9754e068,
  0xf9b61e064,
  0xf9f6e605f,
  0xfa37a405c,
  0xfa785c057,
  0xfab90a053,
  0xfaf9b004f,
  0xfb3a4e04b,
  0xfb7ae4047,
  0xfbbb72043,
  0xfbfbf803f,
  0xfc3c7603b,
  0xfc7cec036,
  0xfcbd58033,
  0xfcfdbe02e,
  0xfd3e1a02a,
  0xfd7e6e027,
  0xfdbebc022,
  0xfdff0001e,
  0xfe3f3c01a,
  0xfe7f70016,
  0xfebf9c012,
  0xfeffc000e,
  0xff3fdc00a,
  0xff7ff0006,
  0xffbffc002
};
