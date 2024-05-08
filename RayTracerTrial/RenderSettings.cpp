#include "RenderSettings.h"
#include "Defaults.h"
#include <stdio.h>


RenderSettings::RenderSettings() {

    resolutionWidth = Defaults::ResolutionWidth;
    resolutionHeight = Defaults::ResolutionHeight;
    maxDepth = Defaults::MaxDepth;

    indirectDiffuse = Defaults::IndirectDiffuse;
    indirectSpecular = Defaults::IndirectSpecular;
}

int RenderSettings::getResolutionWidth() const {

    return resolutionWidth;
}

int RenderSettings::getResolutionHeight() const {
    return resolutionHeight;
}

void RenderSettings::setResolution(int _width, int _height) {

    resolutionWidth = _width;
    resolutionHeight = _height;
}


int RenderSettings::getMaxDepth() const {
    return maxDepth;
}

void RenderSettings::setMaxDepth(int _maxDepth) {
    maxDepth = _maxDepth;
}


int RenderSettings::getDiffuseLayerCount() const {
    return diffuseLayerCount;
}

void RenderSettings::setDiffuseLayerCount(int _layer) {
    diffuseLayerCount = _layer;
}

int RenderSettings::getSpecularLayerCount() const {
    return specularLayerCount;
}

void RenderSettings::setSpecularLayerCount(int _layer) {
    specularLayerCount = _layer;
}

int RenderSettings::getDiffuseRadialCount() const {
    return diffuseRadialCount;
}

void RenderSettings::setDiffuseRadialCount(int _radial) {
    diffuseRadialCount = _radial;
}

int RenderSettings::getSpecularRadialCount() const {
    return specularRadialCount;
}

void RenderSettings::setSpecularRadialCount(int _radial) {
    specularRadialCount = _radial;
}


float RenderSettings::getIndirectDiffuse() const {
    return indirectDiffuse;
}

void RenderSettings::setIndirectDiffuse(float _indirectDiffuse) {
    indirectDiffuse = _indirectDiffuse;
}

float RenderSettings::getIndirectSpecular() const {
    return indirectSpecular;
}

void RenderSettings::setIndirectSpecular(float _indirectSpecular) {
    indirectSpecular = _indirectSpecular;
}
