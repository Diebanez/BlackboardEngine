//
// Created by diego on 24/07/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "BlackboardRuntime.h"
#include <direct.h>

using namespace BlackboardRuntime;

class TestLayer : public Layer{
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

        m_TrisVertexArray.reset(VertexArray::Create());

        Ref<VertexBuffer> trisVertexBuffer;
        trisVertexBuffer.reset(VertexBuffer::Create(trisVertices, sizeof(trisVertices)));
        BufferLayout trisLayout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color" }
        };
        trisVertexBuffer->SetLayout(trisLayout);
        m_TrisVertexArray->AddVertexBuffer(trisVertexBuffer);

        uint32_t trisIndices[3] = {0, 1, 2 };
        Ref<IndexBuffer> trisIndexBuffer;
        trisIndexBuffer.reset(IndexBuffer::Create(trisIndices, sizeof(trisIndices) / sizeof(uint32_t)));
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

        ShaderSource trisVertexShader = ShaderSource(ShaderType::Vertex, trisVertexSrc);

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

        ShaderSource trisFragmentShader = ShaderSource(ShaderType::Fragment, trisFragmentSrc);

        std::vector<ShaderSource> trisShaderSources = {trisVertexShader, trisFragmentShader};

        m_TrisShader =Shader::Create(trisShaderSources);

        float quadVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        m_QuadVertexArray.reset(VertexArray::Create());

        Ref<VertexBuffer> quadVertexBuffer;
        quadVertexBuffer.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
        BufferLayout quadLayout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float2, "a_TexCoords"}
        };
        quadVertexBuffer->SetLayout(quadLayout);
        m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

        uint32_t quadIndices[6] = {0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
        m_QuadVertexArray->SetIndexBuffer(indexBuffer);

        std::string quadVertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoords;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoords;

			void main()
			{
				v_TexCoords = a_TexCoords;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

        ShaderSource quadVertexShader = ShaderSource(ShaderType::Vertex, quadVertexSrc);

        std::string quadFragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

            in vec2 v_TexCoords;

            uniform vec4 u_Color;
            uniform sampler2D u_Texture;

			void main()
			{
				color = u_Color * texture(u_Texture, v_TexCoords);
			}
		)";

        ShaderSource quadFragmentShader = ShaderSource(ShaderType::Fragment, quadFragmentSrc);

        std::vector<ShaderSource> quadShaderSources = {quadVertexShader, quadFragmentShader};

        m_QuadShader = Shader::Create(quadShaderSources);

        m_Texture = Texture2D::Create("assets/textures/Monobike_U1_Base_Color.png");

        m_QuadShader->Bind();
        m_QuadShader->SetUniform("u_Texture", 0);
    }

    void OnUpdate(float time, TimeStep deltaTime) override {
        m_QuadPosition.y = glm::sin(time);
        m_TrisRotation += deltaTime * 90.0f;

        if (Input::IsKeyPressed(BB_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraSpeed * deltaTime;
        }
        
        if (Input::IsKeyPressed(BB_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraSpeed * deltaTime;
        }

        if (Input::IsKeyPressed(BB_KEY_UP)) {
            m_CameraPosition.y += m_CameraSpeed * deltaTime;
        }

        if (Input::IsKeyPressed(BB_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraSpeed * deltaTime;
        }

        if (Input::IsKeyPressed(BB_KEY_E)) {
            m_CameraRotation += m_CameraRotationSpeed * deltaTime;
        }

        if (Input::IsKeyPressed(BB_KEY_Q)) {
            m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
        }

        RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1});
        RenderCommand::Clear();

        Renderer::BeginScene(m_Camera);

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        int counter = 0;
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        glm::vec4 firstColor(0.3f, 0.2f, 0.8f, 1.0f);
        glm::vec4 secondColor(0.8f, 0.3f, 0.2f, 1.0f);

        m_Texture->Bind();
        for(int y = 0; y < 20; y++){
            for(int x = 0; x < 20; x++){
                glm::vec3 pos(x *0.10f, y*0.10f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scaleMatrix;
                if(counter % 2 != 0) {
                    m_QuadShader->SetUniform("u_Color", firstColor);
                }else{
                    m_QuadShader->SetUniform("u_Color", secondColor);
                }

                Renderer::Submit(m_QuadShader, m_QuadVertexArray, glm::translate(glm::mat4(1.0f), m_QuadPosition) * transform);

                counter++;
            }
            counter++;
        }

        m_QuadShader->SetUniform("u_Color", glm::vec4(1.0f));

        Renderer::Submit(m_QuadShader, m_QuadVertexArray, glm::rotate(glm::mat4(1.0f), glm::radians(m_TrisRotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        Renderer::EndScene();
    }

private:
    Ref<Shader> m_TrisShader;
    Ref<VertexArray> m_TrisVertexArray;
    Ref<Shader> m_QuadShader;
    Ref<VertexArray> m_QuadVertexArray;
    Ref<Texture2D> m_Texture;
    OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;

    glm::vec3 m_QuadPosition;
    float  m_TrisRotation;

    float m_CameraSpeed = 1.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 5.0f;

};

class TestApplication : public Application {
public:
    TestApplication() {
        this->PushLayer(new TestLayer);
        this->GetWindow().SetVSync(true);
    }

    ~TestApplication() {
    }


};

Application* BlackboardRuntime::CreateApplication() {
    return new TestApplication();
}
