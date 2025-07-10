//
// Created by tbatt on 19/04/2020.
//

#ifndef OPENGLPLOTLIVE_PROJ_SHADERSET_H
#define OPENGLPLOTLIVE_PROJ_SHADERSET_H

// Standard Includes
#include <memory>

// Project Includes
#include "../texts/CharacterLoader.h"
#include "../textures/TextureManager.h"
#include "shader.h"

namespace GLPL
{

    // Contains the shaders for plotting
    class ShaderSet
    {
    public:
        // Constructor
        ShaderSet();

        // Functions
        const GLchar *getFontPath();
        float getXDpiScaling();
        float getYDpiScaling();
        std::shared_ptr<Shader> getTextShader();
        std::shared_ptr<Shader> getPlot2dShader();
        std::shared_ptr<Shader> getPlot2dLogxShader();
        std::shared_ptr<Shader> getPlot2dLogyShader();
        std::shared_ptr<Shader> getPlot2dLogxLogyShader();
        std::shared_ptr<Shader> getScatter2dShader();
        std::shared_ptr<Shader> getScatter2dLogxShader();
        std::shared_ptr<Shader> getScatter2dLogyShader();
        std::shared_ptr<Shader> getScatter2dLogxLogyShader();
        std::shared_ptr<Shader> getTextureShader();
        std::shared_ptr<Shader> getPlotPosNeg2DShader();
        std::shared_ptr<Shader> getPlotTransparent2dShader();
        std::shared_ptr<CharacterLoader> getCharacterLoader();
        std::shared_ptr<TextureManager> getTextureManager();

    private:
        // DPI Scaling
        float xScaleDpi = 1;
        float yScaleDpi = 1;

        // Shaders
        Shader textShader =
            Shader("bin/Shaders/font.vs", "bin/Shaders/font.frag");
        Shader plot2dShader =
            Shader("bin/Shaders/plot2d.vs", "bin/Shaders/plot2d.frag");
        Shader plot2dShaderLogx =
            Shader("bin/Shaders/plot2dLogx.vs", "bin/Shaders/plot2d.frag");
        Shader plot2dShaderLogy =
            Shader("bin/Shaders/plot2dLogy.vs", "bin/Shaders/plot2d.frag");
        Shader plot2dShaderLogxLogy =
            Shader("bin/Shaders/plot2dLogxLogy.vs", "bin/Shaders/plot2d.frag");
        Shader scatter2dShader =
            Shader("bin/Shaders/scatter2d.vs", "bin/Shaders/scatter2d.frag");
        Shader scatter2dLogxShader = Shader("bin/Shaders/scatter2dLogx.vs",
                                            "bin/Shaders/scatter2d.frag");
        Shader scatter2dLogyShader = Shader("bin/Shaders/scatter2dLogy.vs",
                                            "bin/Shaders/scatter2d.frag");
        Shader scatter2dLogxLogyShader = Shader(
            "bin/Shaders/scatter2dLogxLogy.vs", "bin/Shaders/scatter2d.frag");
        Shader textureShader =
            Shader("bin/Shaders/texture.vs", "bin/Shaders/texture.frag");
        Shader plotPosNeg2DShader = Shader("bin/Shaders/plotPosNeg2d.vs",
                                           "bin/Shaders/plotPosNeg2d.frag");
        Shader plotTransparent2dShader =
            Shader("bin/Shaders/plotTransparent2d.vs",
                   "bin/Shaders/plotTransparent2d.frag");

        // shared_ptr
        std::shared_ptr<Shader> textShaderPt;
        std::shared_ptr<Shader> plot2dShaderPt;
        std::shared_ptr<Shader> plot2dLogxShaderPt;
        std::shared_ptr<Shader> plot2dLogyShaderPt;
        std::shared_ptr<Shader> plot2dLogxLogyShaderPt;
        std::shared_ptr<Shader> scatter2dShaderPt;
        std::shared_ptr<Shader> scatter2dLogxShaderPt;
        std::shared_ptr<Shader> scatter2dLogyShaderPt;
        std::shared_ptr<Shader> scatter2dLogxLogyShaderPt;
        std::shared_ptr<Shader> textureShaderPt;
        std::shared_ptr<Shader> plotPosNeg2DShaderPt;
        std::shared_ptr<Shader> plotTransparent2dShaderPt;
        std::shared_ptr<TextureManager> textureMangerPt;

        // Text
        std::shared_ptr<CharacterLoader> characterLoaderPt;
        // Textures
        TextureManager textureManager = TextureManager();
    };

} // namespace GLPL

#endif // OPENGLPLOTLIVE_PROJ_SHADERSET_H
