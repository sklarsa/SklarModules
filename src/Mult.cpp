#include "SklarModules.hpp"

struct Mult : Module {
    enum ParamIds {
        NUM_PARAMS
    };
    enum InputIds {
        INPUT_A,
        NUM_INPUTS
    };
    enum OutputIds {
        OUTPUT_A,
        OUTPUT_B,
        OUTPUT_C,
        OUTPUT_D,
        OUTPUT_E,
        OUTPUT_F,
        OUTPUT_G,
        OUTPUT_H,
        OUTPUT_I,
        NUM_OUTPUTS
    };
    enum LightIds
    {
        NUM_LIGHTS
    };

    Mult() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
    void step() override;
};

void Mult::step(){
    float input_a = inputs[INPUT_A].value;

    for (int x = 0; x < NUM_OUTPUTS ; x++){
        outputs[x].value = clampf(input_a, -5.0, 5.0);
    }
}

MultWidget::MultWidget()
{
    Mult *module = new Mult();
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

    addInput(createInput<PJ301MPort>(Vec(33, 75), module, Mult::INPUT_A));

    addOutput(createOutput<PJ301MPort>(Vec(33, 125), module, Mult::OUTPUT_A));
    addOutput(createOutput<PJ301MPort>(Vec(33, 150), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 175), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 200), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 225), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 250), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 275), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 300), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 325), module, Mult::OUTPUT_B));
}
