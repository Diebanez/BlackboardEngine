//
// Created by diego on 24/07/2020.
//

#include <glad/glad.h>
#include "BlackboardRuntime.h"

class TestLayer : public BlackboardRuntime::Layer{
public:
    TestLayer(){
        m_VertexArray.reset(BlackboardRuntime::VertexArray::Create());

        float vertices[3 * 4] = {
                -0.75f, -0.75f, 0.0f,
                0.75f, -0.75f, 0.0f,
                0.75f,  0.75f, 0.0f,
                -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<BlackboardRuntime::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(BlackboardRuntime::VertexBuffer::Create(vertices, sizeof(vertices)));
        BlackboardRuntime::BufferLayout layout = {
                {BlackboardRuntime::ShaderDataType::Float3, "a_Position"},
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<BlackboardRuntime::IndexBuffer> indexBuffer;
        indexBuffer.reset(BlackboardRuntime::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

        BlackboardRuntime::ShaderSource vertexShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Vertex, vertexSrc);

        std::string fragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

        BlackboardRuntime::ShaderSource fragmentShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Fragment, fragmentSrc);

        std::vector<BlackboardRuntime::ShaderSource> shaderSources = {vertexShader, fragmentShader};

        m_Shader.reset(BlackboardRuntime::Shader::Create(shaderSources));
    }

    void OnRender() override {
        m_Shader->Bind();
        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

private:
    std::shared_ptr<BlackboardRuntime::Shader> m_Shader;
    std::shared_ptr<BlackboardRuntime::VertexArray> m_VertexArray;

    std::shared_ptr<BlackboardRuntime::Shader> m_BlueShader;
    std::shared_ptr<BlackboardRuntime::VertexArray> m_SquareVertexArray;

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
