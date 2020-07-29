//
// Created by diego on 24/07/2020.
//

#include "BlackboardRuntime.h"

class TestApplication : public BlackboardRuntime::Application {
public:
    TestApplication() {
        m_VertexArray.reset(BlackboardRuntime::VertexArray::Create());

        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<BlackboardRuntime::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(BlackboardRuntime::VertexBuffer::Create(vertices, sizeof(vertices)));
        BlackboardRuntime::BufferLayout layout = {
                {BlackboardRuntime::ShaderDataType::Float3, "a_Position"},
                {BlackboardRuntime::ShaderDataType::Float4, "a_Color"}
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<BlackboardRuntime::IndexBuffer> indexBuffer;
        indexBuffer.reset(BlackboardRuntime::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
			#version 330 core

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

        BlackboardRuntime::ShaderSource vertexShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Vertex, vertexSrc);

        std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

        BlackboardRuntime::ShaderSource fragmentShader = BlackboardRuntime::ShaderSource(BlackboardRuntime::ShaderType::Fragment, fragmentSrc);

        std::vector<BlackboardRuntime::ShaderSource> shaderSources = {vertexShader, fragmentShader};

        m_Shader.reset(BlackboardRuntime::Shader::Create(shaderSources));
    }

    ~TestApplication() {
    }

private:
    std::shared_ptr<BlackboardRuntime::Shader> m_Shader;
    std::shared_ptr<BlackboardRuntime::VertexArray> m_VertexArray;

    std::shared_ptr<BlackboardRuntime::Shader> m_BlueShader;
    std::shared_ptr<BlackboardRuntime::VertexArray> m_SquareVertexArray;

};

BlackboardRuntime::Application *BlackboardRuntime::CreateApplication() {
    return new TestApplication();
}
