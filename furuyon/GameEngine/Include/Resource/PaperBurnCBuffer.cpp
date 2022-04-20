
#include "PaperBurnCBuffer.h"
#include "ConstantBuffer.h"

CPaperBurnCBuffer::CPaperBurnCBuffer() :
    m_BufferData{}
{
    m_BufferData.InLineColor = Vector3(1.f, 0.7529f, 0.7529f) * 2.f;
    m_BufferData.OutLineColor = Vector3(1.f, 1.f, 1.f);
    m_BufferData.CenterColor = Vector3(1.f, 0.7529f, 0.7529f);
    m_BufferData.OutFilter = 0.3f;
    m_BufferData.CenterFilter = 0.1f;
    m_BufferData.InFilter = 0.05f;
}

CPaperBurnCBuffer::CPaperBurnCBuffer(const CPaperBurnCBuffer& buffer) :
    CConstantBufferData(buffer)
{
    m_BufferData = buffer.m_BufferData;
}

CPaperBurnCBuffer::~CPaperBurnCBuffer()
{
}

bool CPaperBurnCBuffer::Init()
{
    SetConstantBuffer("PaperBurnCBuffer");

    return true;
}

void CPaperBurnCBuffer::UpdateCBuffer()
{
    m_pBuffer->UpdateBuffer(&m_BufferData);
}

CPaperBurnCBuffer* CPaperBurnCBuffer::Clone()
{
    return new CPaperBurnCBuffer(*this);
}
