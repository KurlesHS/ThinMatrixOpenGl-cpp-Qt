#include "renderer.h"

Renderer::Renderer(RawModelSharedPtr model) :
    mModel(model)
{

}

void Renderer::render()
{
    prepare();
    render(mModel);
}


void Renderer::render(RawModelSharedPtr model)
{
    glBindVertexArray(model->vaoId());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, model->vertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}


void Renderer::prepare()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
