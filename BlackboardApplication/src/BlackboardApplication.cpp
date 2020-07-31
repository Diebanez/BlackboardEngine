//
// Created by diego on 24/07/2020.
//

#include <glad/glad.h>
#include "BlackboardRuntime.h"

using namespace BlackboardRuntime;

class TestLayer : public BlackboardRuntime::Layer{
public:
    TestLayer(){
        float trisVertices[7 * 3] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0, 1.0f, 0.0f, 1.0f,
                0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        m_TrisVertexArray.reset(BlackboardRuntime::VertexArray::Create());

        std::shared_ptr<BlackboardRuntime::VertexBuffer> trisVertexBuffer;
        trisVertexBuffer.reset(BlackboardRuntime::VertexBuffer::Create(trisVertices, sizeof(trisVertices)));
        BlackboardRuntime::BufferLayout trisLayout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color" }
        };
        trisVertexBuffer->SetLayout(trisLayout);
        m_TrisVertexArray->AddVertexBuffer(trisVertexBuffer);

        uint32_t trisIndices[3] = {0, 1, 2 };
        std::shared_ptr<BlackboardRuntime::IndexBuffer> trisIndexBuffer;
        trisIndexBuffer.reset(BlackboardRuntime::IndexBuffer::Create(trisIndices, sizeof(trisIndices) / sizeof(uint32_t)));
        m_TrisVertexArray->SetIndexBuffer(trisIndexBuffer);

        std::string trisVertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

        BlackboardRuntime::ShaderSource trisVertexShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Vertex, trisVertexSrc);

        std::string trisFragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}
		)";

        BlackboardRuntime::ShaderSource trisFragmentShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Fragment, trisFragmentSrc);

        std::vector<BlackboardRuntime::ShaderSource> trisShaderSources = {trisVertexShader, trisFragmentShader};

        m_TrisShader.reset(BlackboardRuntime::Shader::Create(trisShaderSources));

        float quadVertices[3 * 4] = {
                -0.75f, -0.75f, 0.0f,
                0.75f, -0.75f, 0.0f,
                0.75f,  0.75f, 0.0f,
                -0.75f,  0.75f, 0.0f
        };

        m_QuadVertexArray.reset(BlackboardRuntime::VertexArray::Create());

        std::shared_ptr<BlackboardRuntime::VertexBuffer> quadVertexBuffer;
        quadVertexBuffer.reset(BlackboardRuntime::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
        BlackboardRuntime::BufferLayout quadLayout = {
                {BlackboardRuntime::ShaderDataType::Float3, "a_Position"},
        };
        quadVertexBuffer->SetLayout(quadLayout);
        m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

        uint32_t quadIndices[6] = {0, 1, 2, 2, 3, 0 };
        std::shared_ptr<BlackboardRuntime::IndexBuffer> indexBuffer;
        indexBuffer.reset(BlackboardRuntime::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
        m_QuadVertexArray->SetIndexBuffer(indexBuffer);

        std::string quadVertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

        BlackboardRuntime::ShaderSource quadVertexShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Vertex, quadVertexSrc);

        std::string quadFragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

        BlackboardRuntime::ShaderSource quadFragmentShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Fragment, quadFragmentSrc);

        std::vector<BlackboardRuntime::ShaderSource> quadShaderSources = {quadVertexShader, quadFragmentShader};

        m_QuadShader.reset(BlackboardRuntime::Shader::Create(quadShaderSources));
    }


    void OnRender() override {
        m_QuadShader->Bind();
        m_QuadVertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_QuadVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        m_TrisShader->Bind();
        m_TrisVertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_TrisVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

private:
    std::shared_ptr<Shader> m_TrisShader;
    std::shared_ptr<VertexArray> m_TrisVertexArray;
    std::shared_ptr<Shader> m_QuadShader;
    std::shared_ptr<VertexArray> m_QuadVertexArray;

};

class TestApplication : public BlackboardRuntime::Application {
public:
    TestApplication() {
        this->PushLayer(new TestLayer);
    }

    ~TestApplication() {
    }


};

BlackboardRuntime::Application *BlackboardRuntime::CreateApplication() {
    return new TestApplication();
}
