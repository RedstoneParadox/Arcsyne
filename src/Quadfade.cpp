#include "plugin.hpp"


struct Quadfade : Module {
	enum ParamId {
		X_KNOB_PARAM,
		Y_KNOB_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		X_CV_INPUT,
		INPUT_A_INPUT,
		INPUT_B_INPUT,
		Y_CV_INPUT,
		INPUT_C_INPUT,
		INPUT_D_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUT_A_OUTPUT,
		OUTPUT_B_OUTPUT,
		OUTPUT_MIXED_OUTPUT,
		OUTPUT_C_OUTPUT,
		OUTPUT_D_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Quadfade() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(X_KNOB_PARAM, 0.f, 1.f, 0.f, "x fade");
		configParam(Y_KNOB_PARAM, 0.f, 1.f, 0.f, "y fade");
		configInput(X_CV_INPUT, "x cv");
		configInput(INPUT_A_INPUT, "input a");
		configInput(INPUT_B_INPUT, "input b");
		configInput(Y_CV_INPUT, "y cv");
		configInput(INPUT_C_INPUT, "input c");
		configInput(INPUT_D_INPUT, "input d");
		configOutput(OUTPUT_A_OUTPUT, "output a");
		configOutput(OUTPUT_B_OUTPUT, "output b");
		configOutput(OUTPUT_MIXED_OUTPUT, "output mixed");
		configOutput(OUTPUT_C_OUTPUT, "output c");
		configOutput(OUTPUT_D_OUTPUT, "output d");
	}

	void process(const ProcessArgs& args) override {
		float x_fade = params[X_KNOB_PARAM].getValue();
		float y_fade = params[Y_KNOB_PARAM].getValue();

		
	}
};


struct QuadfadeWidget : ModuleWidget {
	QuadfadeWidget(Quadfade* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Quadfade.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(45.5, -12.772)), module, Quadfade::X_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(-64.994, 12.628)), module, Quadfade::X_KNOB_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(55.165, -9.228)), module, Quadfade::X_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.1, 13.1)), module, Quadfade::INPUT_A_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.3, 13.1)), module, Quadfade::INPUT_B_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(-55.329, 16.172)), module, Quadfade::Y_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.1, 24.3)), module, Quadfade::INPUT_C_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.3, 24.3)), module, Quadfade::INPUT_D_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.1, 104.1)), module, Quadfade::OUTPUT_A_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(18.3, 104.1)), module, Quadfade::OUTPUT_B_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(12.7, 109.7)), module, Quadfade::OUTPUT_MIXED_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.1, 115.3)), module, Quadfade::OUTPUT_C_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(18.3, 115.3)), module, Quadfade::OUTPUT_D_OUTPUT));
	}
};


Model* modelQuadfade = createModel<Quadfade, QuadfadeWidget>("Quadfade");