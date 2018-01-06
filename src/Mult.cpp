#include "SklarModules.hpp"

struct Mult : Module {
    enum ParamIds
    {
        NUM_PARAMS
    };
    enum InputIds
    {
        INPUT_A,
        NUM_INPUTS
    };
    enum OutputIds
    {
        OUTPUT_A,
        OUTPUT_B,
        OUTPUT_C,
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

    outputs[OUTPUT_A].value = clampf(input_a, -5.0, 5.0);
    outputs[OUTPUT_B].value = clampf(input_a, -5.0, 5.0);
    outputs[OUTPUT_C].value = clampf(input_a, -5.0, 5.0);
}

MultWidget::MultWidget()
{
    Mult *module = new Mult();
    setModule(module);
    box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

    {
        SVGPanel *panel = new SVGPanel();
        panel->box.size = box.size;
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/MyModule.svg")));
        addChild(panel);
    }

    addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(33, 120), module, Mult::INPUT_A));

    addOutput(createOutput<PJ301MPort>(Vec(33, 150), module, Mult::OUTPUT_A));
    addOutput(createOutput<PJ301MPort>(Vec(33, 170), module, Mult::OUTPUT_B));
    addOutput(createOutput<PJ301MPort>(Vec(33, 190), module, Mult::OUTPUT_C));
}
