#include "plugin.hpp"


struct Manifold : Module {
	enum ParamId {
		L_KNOB_1_PARAM,
		R_KNOB_1_PARAM,
		C_KNOB_1_PARAM,
		L_KNOB_2_PARAM,
		R_KNOB_2_PARAM,
		C_KNOB_2_PARAM,
		INSIDE_KNOB_PARAM,
		L_KNOB_3_PARAM,
		R_KNOB_3_PARAM,
		INSIDE_ATT_PARAM,
		C_KNOB_3_PARAM,
		L_KNOB_4_PARAM,
		R_KNOB_4_PARAM,
		SWAP_ATT_PARAM,
		C_KNOB_4_PARAM,
		SWAP_KNOB_PARAM,
		L_KNOB_5_PARAM,
		R_KNOB_5_PARAM,
		C_KNOB_5_PARAM,
		L_KNOB_6_PARAM,
		R_KNOB_6_PARAM,
		C_KNOB_6_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		RESET_INPUT,
		INSIDE_CV_INPUT,
		SWAP_CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		CV_OUTPUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Manifold() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(L_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(INSIDE_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(INSIDE_ATT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWAP_ATT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWAP_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
		configInput(CLOCK_INPUT, "");
		configInput(RESET_INPUT, "");
		configInput(INSIDE_CV_INPUT, "");
		configInput(SWAP_CV_INPUT, "");
		configOutput(CV_OUTPUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		
	}
};


struct ManifoldWidget : ModuleWidget {
	ManifoldWidget(Manifold* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Manifold.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.18, 23.0)), module, Manifold::L_KNOB_1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.18, 23.0)), module, Manifold::R_KNOB_1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 30.5)), module, Manifold::C_KNOB_1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.18, 38.0)), module, Manifold::L_KNOB_2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.18, 38.0)), module, Manifold::R_KNOB_2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 45.5)), module, Manifold::C_KNOB_2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(13.1, 48.75)), module, Manifold::INSIDE_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.18, 53.0)), module, Manifold::L_KNOB_3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.18, 53.0)), module, Manifold::R_KNOB_3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(17.85, 59.6)), module, Manifold::INSIDE_ATT_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 60.5)), module, Manifold::C_KNOB_3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.18, 68.0)), module, Manifold::L_KNOB_4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.18, 68.0)), module, Manifold::R_KNOB_4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.35, 69.6)), module, Manifold::SWAP_ATT_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 75.5)), module, Manifold::C_KNOB_4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(13.1, 79.75)), module, Manifold::SWAP_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.18, 83.0)), module, Manifold::L_KNOB_5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.18, 83.0)), module, Manifold::R_KNOB_5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.18, 90.5)), module, Manifold::C_KNOB_5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.18, 98.0)), module, Manifold::L_KNOB_6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(54.18, 98.0)), module, Manifold::R_KNOB_6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43.55, 105.5)), module, Manifold::C_KNOB_6_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.1, 16.1)), module, Manifold::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.1, 26.1)), module, Manifold::RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.1, 59.35)), module, Manifold::INSIDE_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.1, 69.574)), module, Manifold::SWAP_CV_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(13.1, 105.082)), module, Manifold::CV_OUTPUT_OUTPUT));
	}
};


Model* modelManifold = createModel<Manifold, ManifoldWidget>("Manifold");