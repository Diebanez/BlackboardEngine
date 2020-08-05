//
// Created by diego on 24/07/2020.
//

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "BlackboardRuntime.h"

class TestLayer : public BlackboardRuntime::Layer{
public:
    TestLayer() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
    m_CameraPosition(0.0f),
    m_QuadPosition(0.0f),
    m_TrisRotation(0.0f) {
        float trisVertices[7 * 3] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0, 1.0f, 0.0f, 1.0f,
                0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        m_TrisVertexArray.reset(BlackboardRuntime::VertexArray::Create());

        std::shared_ptr<BlackboardRuntime::VertexBuffer> trisVertexBuffer;
        trisVertexBuffer.reset(BlackboardRuntime::VertexBuffer::Create(trisVertices, sizeof(trisVertices)));
        BlackboardRuntime::BufferLayout trisLayout = {
                {BlackboardRuntime::ShaderDataType::Float3, "a_Position"},
                {BlackboardRuntime::ShaderDataType::Float4, "a_Color" }
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

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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


    void OnUpdate(float time, BlackboardRuntime::TimeStep deltaTime) override {
        m_QuadPosition.y = glm::sin(time);
        m_TrisRotation += deltaTime * 90.0f;

        if (BlackboardRuntime::Input::IsKeyPressed(BB_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraSpeed * deltaTime;
        }
        
        if (BlackboardRuntime::Input::IsKeyPressed(BB_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraSpeed * deltaTime;
        }

        if (BlackboardRuntime::Input::IsKeyPressed(BB_KEY_UP)) {
            m_CameraPosition.y += m_CameraSpeed * deltaTime;
        }

        if (BlackboardRuntime::Input::IsKeyPressed(BB_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraSpeed * deltaTime;
        }

        if (BlackboardRuntime::Input::IsKeyPressed(BB_KEY_E)) {
            m_CameraRotation += m_CameraRotationSpeed * deltaTime;
        }

        if (BlackboardRuntime::Input::IsKeyPressed(BB_KEY_Q)) {
            m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
        }

        BlackboardRuntime::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1});
        BlackboardRuntime::RenderCommand::Clear();

        BlackboardRuntime::Renderer::BeginScene(m_Camera);

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        BlackboardRuntime::Renderer::Submit(m_QuadShader, m_QuadVertexArray, glm::translate(glm::mat4(1.0f), m_QuadPosition));
        BlackboardRuntime::Renderer::Submit(m_TrisShader, m_TrisVertexArray, glm::rotate(glm::mat4(1.0f), glm::radians(m_TrisRotation), glm::vec3(0, 0, 1)));

        BlackboardRuntime::Renderer::EndScene();
    }

private:
    std::shared_ptr<BlackboardRuntime::Shader> m_TrisShader;
    std::shared_ptr<BlackboardRuntime::VertexArray> m_TrisVertexArray;
    std::shared_ptr<BlackboardRuntime::Shader> m_QuadShader;
    std::shared_ptr<BlackboardRuntime::VertexArray> m_QuadVertexArray;
    BlackboardRuntime::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;

    glm::vec3 m_QuadPosition;
    float  m_TrisRotation;

    float m_CameraSpeed = 1.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 5.0f;

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
