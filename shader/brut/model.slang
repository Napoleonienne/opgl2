import 

// L'ordre et la discipline remplacent le chaos des variables globales
struct VertexInput
{
    [[vk::location(0)]] float3 aPos      : POSITION;
    [[vk::location(1)]] float2 aPosTEX   : TEXCOORD0;
    [[vk::location(2)]] float3 aNORMALE  : NORMAL;
};

struct VertexOutput
{
    float3 normale     : NORMAL;
    float3 FragPos     : POSITION;
    float2 postexture  : TEXCOORD0;
    
    // La sémantique sacrée de la position finale
    float4 position    : SV_Position; 
};

cbuffer ParametresTransformations
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

[shader("vertex")]
VertexOutput main(VertexInput input)
{
    VertexOutput output;

    // L'élégance de la multiplication matricielle via mul()
    float4x4 PVM = mul(projection, mul(view, model));
    
    // Je vous laisse votre aberration spatiale à 0.5. 
    // Votre code est transformé, mais vos péchés y survivent.
    output.position = mul(PVM, float4(input.aPos, 0.5)); 
    
    // Le monde physique tel que déformé par votre modèle
    output.FragPos = mul(model, float4(input.aPos, 1.0)).xyz;

    // La flagellation computationnelle continue avec une conversion explicite
    float3x3 normalMatrix = (float3x3)transpose(inverse(model));
    output.normale = mul(normalMatrix, input.aNORMALE);

    output.postexture = input.aPosTEX;

    return output;
}