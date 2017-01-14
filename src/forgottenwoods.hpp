#include <fea/structure.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include <fea/render2d.hpp>
#include "player/inputlogic.hpp"
#include "messages.hpp"
#include "land/chunklogic.hpp"
#include <gamedata.hpp>
#include <spr/data/alltypes.hpp>
#include <data/alltypes.hpp>

#include <spr/rendering/renderlogic.hpp>
#include <spr/entitystates/entitystateslogic.hpp>
#include <spr/physics/collisionlogic.hpp>
#include "entity/entitylogic.hpp"
#include "camera/cameralogic.hpp"

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
        void loadResources();
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
        spr::EntityStatesLogic mEntityStatesLogic;
        EntityLogic mEntityLogic;
        spr::CollisionLogic mCollisionLogic;

        //InterfaceLogic mInterfaceLogic;
        spr::RenderLogic mRenderLogic;

        void temp();
};
