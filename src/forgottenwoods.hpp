#include <fea/structure.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include <fea/render2d.hpp>
#include "inputhandler.hpp"
#include "messages.hpp"
#include "audioplayer.hpp"
#include "land/chunkpipeline.hpp"
#include <data.hpp>

#include "renderlogic.hpp"

class ForgottenWoods : public fea::Application,
    public fea::MessageReceiver<QuitMessage,
    ResizeMessage,
    KeyPressedMessage,
    MouseClickMessage,
    MouseReleaseMessage,
    MouseMoveMessage,
    MouseWheelMessage>
{
    public:
        ForgottenWoods();
        void handleMessage(const QuitMessage& message) override;
        void handleMessage(const ResizeMessage& message) override;
        void handleMessage(const KeyPressedMessage& message) override;
        void handleMessage(const MouseClickMessage& message) override;
        void handleMessage(const MouseReleaseMessage& message) override;
        void handleMessage(const MouseMoveMessage& message) override;
        void handleMessage(const MouseWheelMessage& message) override;
		void startScenario();
    protected:
        void loop() override;
    private:

        glm::ivec2 mWindowSize;

        //fea
        fea::MessageBus mBus;
        fea::Window mWindow;
        fea::Renderer2D mFeaRenderer;
        fea::InputHandler mFeaInputHandler;

        //input
        InputHandler mInputHandler;

        //system
        th::Optional<int32_t> mClickedEntity;

        GameData mData;

        //AudioPlayer mAudioPlayer;
        
        fea::Texture mImguiFontTexture;

        bool mGuiBlocksMouse;

        //logic
        ChunkPipeline mChunkPipeline;

        //InterfaceLogic mInterfaceLogic;
        RenderLogic mRenderLogic;

        void temp();
};
