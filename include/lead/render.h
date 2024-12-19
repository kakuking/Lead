#pragma once

#include <lead/common.h>
#include <lead/scene.h>
#include <lead/sampler.h>
#include <lead/camera.h>
#include <lead/color.h>
#include <lead/integrator.h>
#include <lead/leadexception.h>

#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfRgba.h>

#include <iostream>
#include <fstream>

LEAD_NAMESPACE_BEGIN
class Renderer {
public:
    Renderer(const Scene* scene) {
        m_scene = scene;

        m_sampler = m_scene->getSampler();
        m_camera = m_scene->getCamera();
        m_integrator = m_scene->getIntegrator();

        m_image = new std::vector<Color3f>();
        m_imf_image = new std::vector<Imf::Rgba>();
    }

    void setBlocksize(int newSize) {
        m_blocksize = newSize;
    }

    void render(const std::string& filename) {
        std::cout << "Render function\n";
        Point2f outputSize = m_camera->getOutputSize();
        std::cout << tfm::format("Output size: %s\n", outputSize.toString());

        m_image->resize(outputSize.x() * outputSize.y());
        m_imf_image->resize(outputSize.x() * outputSize.y());

        std::cout << "About to get number of samples\n";
        float num_samples = (float)m_sampler->getSampleCount();
        
        std::cout << "About to render\n";

        for (size_t i = 0; i < outputSize.x(); i++) {
        for (size_t j = 0; j < outputSize.y(); j++) {
        for (size_t k = 0; k < num_samples; k++) {
            int idx = (int)outputSize.x() * j + i;
            Ray3f ray = m_camera->sampleRay(Point2f(i, j));
            (*m_image)[idx] += m_integrator->Li(m_scene, m_sampler, ray);
        }}}

        std::cout << "About to divide\n";

        for (size_t i = 0; i < m_image->size(); i++) {
            (*m_image)[i] /= num_samples;

            (*m_imf_image)[i] = Imf::Rgba((*m_image)[i].x, (*m_image)[i].y, (*m_image)[i].z, 1.f);
        }
        

        std::cout << "Writing to file\n";

        writeToFile(filename, (int)outputSize.x(), (int)outputSize.y());
    }

    void writeToFile(const std::string& filename, int width, int height) {
        try {
            Imf::RgbaOutputFile file(filename.c_str(), width, height, Imf::WRITE_RGBA);

            file.setFrameBuffer(m_imf_image->data(), 1, width);
            file.writePixels(height);
        } catch (const std::exception& e) {
            throw LeadException("Error in writing to EXR file!");
        }
    }

protected:
    const Scene* m_scene;
    const Camera* m_camera;
    const Integrator* m_integrator;
    Sampler* m_sampler;

    int m_blocksize;

    std::vector<Color3f> *m_image;
    std::vector<Imf::Rgba> *m_imf_image;
};

LEAD_NAMESPACE_END