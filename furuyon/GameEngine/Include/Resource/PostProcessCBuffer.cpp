
#include "PostProcessCBuffer.h"
#include "ConstantBuffer.h"

CPostProcessCBuffer::CPostProcessCBuffer() :
    m_BufferData{}
{
}

CPostProcessCBuffer::CPostProcessCBuffer(const CPostProcessCBuffer& buffer) :
    CConstantBufferData(buffer)
{
    m_BufferData = buffer.m_BufferData;
}

CPostProcessCBuffer::~CPostProcessCBuffer()
{
}

bool CPostProcessCBuffer::Init()
{
    SetConstantBuffer("PostProcessCBuffer");
    SetEmpty(Vector2(0.5f, 1.f));
    return true;
}

void CPostProcessCBuffer::UpdateCBuffer()
{
    m_pBuffer->UpdateBuffer(&m_BufferData);
}

CPostProcessCBuffer* CPostProcessCBuffer::Clone()
{
    return new CPostProcessCBuffer(*this);
}
