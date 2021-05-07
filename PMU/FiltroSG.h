#ifndef FILTROSG_H
#define FILTROSG_H

//#include "../parameters.h"

// Filtro Savitzky-Golay

#if FS_D == 15360
#define N_SG 183
const double SG_coef[N_SG] = {-0.000178189594,-0.000176231466,-0.000174273339,-0.000172315212,-0.000170357084,-0.000168398957,-0.000166440829,-0.000164482702,-0.000162524574,-0.000160566447,-0.000158608320,-0.000156650192,-0.000154692065,-0.000152733937,-0.000150775810,-0.000148817683,-0.000146859555,-0.000144901428,-0.000142943300,-0.000140985173,-0.000139027046,-0.000137068918,-0.000135110791,-0.000133152663,-0.000131194536,-0.000129236409,-0.000127278281,-0.000125320154,-0.000123362026,-0.000121403899,-0.000119445772,-0.000117487644,-0.000115529517,-0.000113571389,-0.000111613262,-0.000109655135,-0.000107697007,-0.000105738880,-0.000103780752,-0.000101822625,-0.000099864498,-0.000097906370,-0.000095948243,-0.000093990115,-0.000092031988,-0.000090073861,-0.000088115733,-0.000086157606,-0.000084199478,-0.000082241351,-0.000080283224,-0.000078325096,-0.000076366969,-0.000074408841,-0.000072450714,-0.000070492587,-0.000068534459,-0.000066576332,-0.000064618204,-0.000062660077,-0.000060701950,-0.000058743822,-0.000056785695,-0.000054827567,-0.000052869440,-0.000050911312,-0.000048953185,-0.000046995058,-0.000045036930,-0.000043078803,-0.000041120675,-0.000039162548,-0.000037204421,-0.000035246293,-0.000033288166,-0.000031330038,-0.000029371911,-0.000027413784,-0.000025455656,-0.000023497529,-0.000021539401,-0.000019581274,-0.000017623147,-0.000015665019,-0.000013706892,-0.000011748764,-0.000009790637,-0.000007832510,-0.000005874382,-0.000003916255,-0.000001958127,0.000000000000,0.000001958127,0.000003916255,0.000005874382,0.000007832510,0.000009790637,0.000011748764,0.000013706892,0.000015665019,0.000017623147,0.000019581274,0.000021539401,0.000023497529,0.000025455656,0.000027413784,0.000029371911,0.000031330038,0.000033288166,0.000035246293,0.000037204421,0.000039162548,0.000041120675,0.000043078803,0.000045036930,0.000046995058,0.000048953185,0.000050911312,0.000052869440,0.000054827567,0.000056785695,0.000058743822,0.000060701950,0.000062660077,0.000064618204,0.000066576332,0.000068534459,0.000070492587,0.000072450714,0.000074408841,0.000076366969,0.000078325096,0.000080283224,0.000082241351,0.000084199478,0.000086157606,0.000088115733,0.000090073861,0.000092031988,0.000093990115,0.000095948243,0.000097906370,0.000099864498,0.000101822625,0.000103780752,0.000105738880,0.000107697007,0.000109655135,0.000111613262,0.000113571389,0.000115529517,0.000117487644,0.000119445772,0.000121403899,0.000123362026,0.000125320154,0.000127278281,0.000129236409,0.000131194536,0.000133152663,0.000135110791,0.000137068918,0.000139027046,0.000140985173,0.000142943300,0.000144901428,0.000146859555,0.000148817683,0.000150775810,0.000152733937,0.000154692065,0.000156650192,0.000158608320,0.000160566447,0.000162524574,0.000164482702,0.000166440829,0.000168398957,0.000170357084,0.000172315212,0.000174273339,0.000176231466,0.000178189594};
#else
#define N_SG 17
const double SG_coef[N_SG] = {0.032163742690058,  -0.004213966288270,  -0.027648778809770, -0.039989680082559,  -0.043085655314757,  -0.038785689714482, -0.028938768489852,  -0.015393876848985,  -0.000000000000000,   0.015393876848985,   0.028938768489852,   0.038785689714482, 0.043085655314757,   0.039989680082559,   0.027648778809770,   0.004213966288270,  -0.032163742690058};
#endif

#define SG_GAIN (FS/(2*PI))

struct SG
{
    double buffSG[N_SG];
    double outSG = 0;
    int k0 = 0;
};

void CalcularSG(SG *sg, double fase);
void AtualizarBufferSG(SG *sg, double fase);

#endif