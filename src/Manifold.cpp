#include "plugin.hpp"
#include "random.hpp"

struct Manifold : Module {
	enum Lane {
		LEFT,
		CENTER,
		RIGHT
	};
	enum ParamId {
		SWAP_ATT_PARAM,
		INSIDE_ATT_PARAM,
		SWAP_KNOB_PARAM,
		INSIDE_KNOB_PARAM,
		L_KNOB_6_PARAM,
		L_KNOB_5_PARAM,
		L_KNOB_4_PARAM,
		L_KNOB_3_PARAM,
		L_KNOB_2_PARAM,
		L_KNOB_1_PARAM,
		C_KNOB_5_PARAM,
		C_KNOB_4_PARAM,
		C_KNOB_6_PARAM,
		C_KNOB_3_PARAM,
		C_KNOB_2_PARAM,
		C_KNOB_1_PARAM,
		R_KNOB_6_PARAM,
		R_KNOB_5_PARAM,
		R_KNOB_4_PARAM,
		R_KNOB_3_PARAM,
		R_KNOB_2_PARAM,
		R_KNOB_1_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		SWAP_CV_INPUT,
		CLOCK_INPUT,
		RESET_INPUT,
		INSIDE_CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		CV_OUTPUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	int step = -1; // -1 if just reset
	Lane currentLane = LEFT;
	Lane currentOutsideLane = LEFT;
	ParamId mapping[3][6];

	Manifold() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(SWAP_ATT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(INSIDE_ATT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SWAP_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(INSIDE_KNOB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(L_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(R_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
		configInput(SWAP_CV_INPUT, "");
		configInput(CLOCK_INPUT, "");
		configInput(RESET_INPUT, "");
		configInput(INSIDE_CV_INPUT, "");
		configOutput(CV_OUTPUT_OUTPUT, "cv");

		// Left Lane
		mapping[0][0] = L_KNOB_1_PARAM;
		mapping[0][1] = L_KNOB_2_PARAM;
		mapping[0][2] = L_KNOB_3_PARAM;
		mapping[0][3] = L_KNOB_4_PARAM;
		mapping[0][4] = L_KNOB_5_PARAM;
		mapping[0][5] = L_KNOB_6_PARAM;
		// Center Lane
		mapping[1][0] = C_KNOB_1_PARAM;
		mapping[1][1] = C_KNOB_2_PARAM;
		mapping[1][2] = C_KNOB_3_PARAM;
		mapping[1][3] = C_KNOB_4_PARAM;
		mapping[1][4] = C_KNOB_5_PARAM;
		mapping[1][5] = C_KNOB_6_PARAM;
		// Right Lane
		mapping[2][0] = R_KNOB_1_PARAM;
		mapping[2][1] = R_KNOB_2_PARAM;
		mapping[2][2] = R_KNOB_3_PARAM;
		mapping[2][3] = R_KNOB_4_PARAM;
		mapping[2][4] = R_KNOB_5_PARAM;
		mapping[2][5] = R_KNOB_6_PARAM;
	}

	void process(const ProcessArgs& args) override {
		bool reset = inputs[RESET_INPUT].getVoltage(0) == 10.f;
		bool triggered = inputs[CLOCK_INPUT].getVoltage(0) == 10.f;

		if (reset) 
		{
			step = -1;
			currentLane = LEFT;
			currentOutsideLane = LEFT;
			if (!triggered) outputs[CV_OUTPUT_OUTPUT].clearVoltages();
		}

		if (triggered) 
		{
			random::Xoroshiro128Plus rng;

			std::uniform_real_distribution<float> uniform(0.f, 1.f);
			float swapPercent = uniform(rng);
			float insidePercent = uniform(rng);

			float swapChance = params[SWAP_KNOB_PARAM].getValue() + (params[SWAP_ATT_PARAM].getValue() * inputs[SWAP_CV_INPUT].getVoltage(0));
			float insideChance = params[INSIDE_KNOB_PARAM].getValue() + (params[SWAP_ATT_PARAM].getValue() * inputs[SWAP_CV_INPUT].getVoltage(0));

			if (step > -1)
			{
				if (currentLane == Lane::CENTER && swapPercent >= swapChance)
				{
					switch (currentOutsideLane)
					{
					case LEFT:
						currentOutsideLane = RIGHT;
						break;
					case RIGHT:
						currentOutsideLane = LEFT;
						break;
					default:
						break;
					}
				}
				if (insidePercent >= insideChance) 
				{
					if (currentLane == Lane::CENTER) {
						currentLane = currentOutsideLane;
					}
					else {
						currentLane = Lane::CENTER;
					}
				} 
				else {
					step++;
				}
			}
			else {
				step++;
			}
			

			step++;
			ParamId id = mapping[currentLane][step];
			float cv = params[id].getValue();
			outputs[CV_OUTPUT_OUTPUT].setVoltage(cv);
		}
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

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(-8.35, -69.6)), module, Manifold::SWAP_ATT_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(-17.85, -59.6)), module, Manifold::INSIDE_ATT_PARAM));
		addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(-79.75, 13.1)), module, Manifold::SWAP_KNOB_PARAM));
		addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(-48.75, 13.1)), module, Manifold::INSIDE_KNOB_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-98.0, 32.18)), module, Manifold::L_KNOB_6_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-83.0, 32.18)), module, Manifold::L_KNOB_5_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-68.0, 32.18)), module, Manifold::L_KNOB_4_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-53.0, 32.18)), module, Manifold::L_KNOB_3_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-38.0, 32.18)), module, Manifold::L_KNOB_2_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-23.0, 32.18)), module, Manifold::L_KNOB_1_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-90.5, 43.18)), module, Manifold::C_KNOB_5_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-75.5, 43.18)), module, Manifold::C_KNOB_4_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-105.5, 43.55)), module, Manifold::C_KNOB_6_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-60.5, 43.18)), module, Manifold::C_KNOB_3_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-45.5, 43.18)), module, Manifold::C_KNOB_2_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-30.5, 43.18)), module, Manifold::C_KNOB_1_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-98.0, 54.18)), module, Manifold::R_KNOB_6_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-83.0, 54.18)), module, Manifold::R_KNOB_5_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-68.0, 54.18)), module, Manifold::R_KNOB_4_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-53.0, 54.18)), module, Manifold::R_KNOB_3_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-38.0, 54.18)), module, Manifold::R_KNOB_2_PARAM));
		addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(-23.0, 54.18)), module, Manifold::R_KNOB_1_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(69.574, -18.1)), module, Manifold::SWAP_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(16.1, -13.1)), module, Manifold::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(26.1, -13.1)), module, Manifold::RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(59.35, -8.1)), module, Manifold::INSIDE_CV_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(13.1, 105.082)), module, Manifold::CV_OUTPUT_OUTPUT));
	}
};


Model* modelManifold = createModel<Manifold, ManifoldWidget>("Manifold");