#include <cstdlib>
#include "dsp/digital.hpp"
#include "SklarModules.hpp"

struct Noise : Module {
    enum ParamIds {
        CLOCK_FREQ_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        CV_INPUT,
        TRIGGER_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        NOISE_OUTPUT,
        SH_OUTPUT,
        NUM_OUTPUTS
    };
    enum LightIds {
        TRIGGER_LIGHT,
        NUM_LIGHTS
    };

    SchmittTrigger trigger;
    float phase = 0.0;

    Noise() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) { }
    void step() override;
    
    
};

void Noise::step(){
    int rnd = rand();

    // Calculate random noise and send to noise output
    float val = (float)rnd / (float)RAND_MAX * 5.0;
    outputs[NOISE_OUTPUT].value = val;

    // Calculate internal clock
    float deltaTime = 1.0 / engineGetSampleRate();


    if (trigger.process(inputs[TRIGGER_INPUT].value)) {
        outputs[SH_OUTPUT].value = inputs[CV_INPUT].normalize(val);
    } 

    if (trigger.isHigh()) {
        lights[TRIGGER_LIGHT].setBrightness(100);
    } else {
        lights[TRIGGER_LIGHT].setBrightness(0);
    }

}

NoiseWidget::NoiseWidget()
{
    Noise *module = new Noise();
    setModule(module);
    box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

    {
        SVGPanel *panel = new SVGPanel();
        panel->box.size = box.size;
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/Mult.svg")));
        addChild(panel);
    }

    addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(33, 80), module, Noise::CV_INPUT));
    addInput(createInput<PJ301MPort>(Vec(33, 105), module, Noise::TRIGGER_INPUT));

    addOutput(createOutput<PJ301MPort>(Vec(33, 150), module, Noise::NOISE_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(33, 175), module, Noise::SH_OUTPUT));

    addChild(createLight<MediumLight<YellowLight>>(Vec(41, 200), module, Noise::TRIGGER_LIGHT));
}
