import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display
from esphome.const import CONF_ID, CONF_DISPLAY_ID

DEPENDENCIES = ["display"]
CODEOWNERS = ["@YourGitHubUsername"]

esp32_eyes_ns = cg.esphome_ns.namespace("esp32_eyes")
Esp32EyesComponent = esp32_eyes_ns.class_("Esp32EyesComponent", cg.Component)

CONF_DISPLAY = "display"
CONF_SCREEN_WIDTH = "screen_width"
CONF_SCREEN_HEIGHT = "screen_height"
CONF_EYE_SIZE = "eye_size"
CONF_EYE_DISTANCE = "eye_distance"
CONF_UPDATE_INTERVAL = "update_interval"
CONF_RANDOM_BEHAVIOR = "random_behavior"
CONF_RANDOM_BLINK = "random_blink"
CONF_RANDOM_LOOK = "random_look"
CONF_BLINK_INTERVAL = "blink_interval"
CONF_LOOK_INTERVAL = "look_interval"
CONF_BEHAVIOR_INTERVAL = "behavior_interval"
CONF_EMOTIONS = "emotions"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Esp32EyesComponent),
    cv.GenerateID(CONF_DISPLAY): cv.use_id(display.Display),
    cv.Optional(CONF_SCREEN_WIDTH, default=128): cv.positive_int,
    cv.Optional(CONF_SCREEN_HEIGHT, default=64): cv.positive_int,
    cv.Optional(CONF_EYE_SIZE, default=20): cv.positive_int,
    cv.Optional(CONF_EYE_DISTANCE, default=4): cv.positive_int,
    cv.Optional(CONF_UPDATE_INTERVAL, default=50): cv.positive_int,
    cv.Optional(CONF_RANDOM_BEHAVIOR, default=True): cv.boolean,
    cv.Optional(CONF_RANDOM_BLINK, default=True): cv.boolean,
    cv.Optional(CONF_RANDOM_LOOK, default=True): cv.boolean,
    cv.Optional(CONF_BLINK_INTERVAL, default=3000): cv.positive_int,
    cv.Optional(CONF_LOOK_INTERVAL, default=2000): cv.positive_int,
    cv.Optional(CONF_BEHAVIOR_INTERVAL, default=5000): cv.positive_int,
    cv.Optional(CONF_EMOTIONS): cv.ensure_list(cv.Schema({
        cv.Required("name"): cv.string,
        cv.Required("weight"): cv.float_,
    })),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    # Get display component
    disp = await cg.get_variable(config[CONF_DISPLAY])
    cg.add(var.set_display(disp))
    
    # Set dimensions
    cg.add(var.set_screen_width(config[CONF_SCREEN_WIDTH]))
    cg.add(var.set_screen_height(config[CONF_SCREEN_HEIGHT]))
    cg.add(var.set_eye_size(config[CONF_EYE_SIZE]))
    cg.add(var.set_eye_distance(config[CONF_EYE_DISTANCE]))
    
    # Set update interval
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    
    # Set behavior modes
    cg.add(var.set_random_behavior(config[CONF_RANDOM_BEHAVIOR]))
    cg.add(var.set_random_blink(config[CONF_RANDOM_BLINK]))
    cg.add(var.set_random_look(config[CONF_RANDOM_LOOK]))
    
    # Set timers
    cg.add(var.set_blink_interval(config[CONF_BLINK_INTERVAL]))
    cg.add(var.set_look_interval(config[CONF_LOOK_INTERVAL]))
    cg.add(var.set_behavior_interval(config[CONF_BEHAVIOR_INTERVAL]))
    
    # Add emotion weights if configured
    if CONF_EMOTIONS in config:
        emotions = {
            "normal": 0,
            "happy": 1,
            "sad": 2,
            "angry": 3,
            "surprised": 4,
            "fearful": 5,
            "disgusted": 6,
            "glee": 7,
            "content": 8,
            "relaxed": 9,
            "focused": 10,
            "confused": 11,
            "frustrated": 12,
            "determined": 13,
            "concerned": 14,
            "expectant": 15,
            "joyful": 16,
            "loving": 17,
        }
        
        for emotion_config in config[CONF_EMOTIONS]:
            emotion_name = emotion_config["name"].lower()
            weight = emotion_config["weight"]
            if emotion_name in emotions:
                emotion_id = emotions[emotion_name]
                cg.add(var.set_emotion(emotion_id, weight))
