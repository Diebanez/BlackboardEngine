//
// Created by diego on 24/07/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "BlackboardRuntime.h"

using namespace BlackboardRuntime;

class TestLayer : public Layer{
public:
    TestLayer() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
                  m_CameraPosition(0.0f),
                  m_QuadPosition(0.0f),
                  m_QuadRotation(0.0f) {

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

        m_QuadShader = Shader::Create("assets/shaders/textureBase.glsl");

        m_Texture = Texture2D::Create("assets/textures/Monobike_U1_Base_Color.png");
        m_Texture2 = Texture2D::Create("assets/textures/BB_Logo_2.png");

        m_QuadShader->Bind();
        m_QuadShader->SetUniform("u_Texture", 0);
    }

    void OnUpdate(float time, TimeStep deltaTime) override {
        m_QuadPosition.y = glm::sin(time);
        m_QuadRotation += deltaTime * 90.0f;

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

        Renderer::Submit(m_QuadShader, m_QuadVertexArray, glm::rotate(glm::mat4(1.0f), glm::radians(m_QuadRotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_Texture2->Bind();
        Renderer::Submit(m_QuadShader, m_QuadVertexArray,  glm::mat4(1.0f));

        Renderer::EndScene();
    }

private:
    Ref<Shader> m_QuadShader;
    Ref<VertexArray> m_QuadVertexArray;
    Ref<Texture2D> m_Texture;
    Ref<Texture2D> m_Texture2;
    OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;

    glm::vec3 m_QuadPosition;
    float  m_QuadRotation;

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
