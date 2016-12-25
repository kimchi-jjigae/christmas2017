#include <fea/structure.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include <fea/render2d.hpp>
#include "player/inputlogic.hpp"
#include "messages.hpp"
#include "audioplayer.hpp"
#include "land/chunklogic.hpp"
#include <data.hpp>

#include "rendering/renderlogic.hpp"
#include "camera/cameralogic.hpp"
#include "entitystates/entitystateslogic.hpp"
#include "entity/entitylogic.hpp"
#include "physics/collisionlogic.hpp"

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
        void spreadHappiness();

        //fea
        fea::MessageBus mBus;
        fea::Window mWindow;
        fea::Renderer2D mFeaRenderer;
        fea::InputHandler mFeaInputHandler;

        GameData mData;

        //input
        InputLogic mInputLogic;

        //system
        th::Optional<int32_t> mClickedEntity;

        //AudioPlayer mAudioPlayer;
        
        fea::Texture mImguiFontTexture;

        bool mGuiBlocksMouse;

        //logic
        ChunkLogic mChunkLogic;
        CameraLogic mCameraLogic;
        EntityStatesLogic mEntityStatesLogic;
        EntityLogic mEntityLogic;
        CollisionLogic mCollisionLogic;

        //InterfaceLogic mInterfaceLogic;
        RenderLogic mRenderLogic;

        void temp();
};
