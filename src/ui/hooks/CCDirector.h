#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/LoadingLayer.hpp>

class $modify(MyCCDirector, CCDirector){

	/*void popScene(){
		CCScene* currentScene = CCDirector::get()->getRunningScene();
		if(!currentScene->getChildByIDRecursive("settings-layer"_spr)){
			if(!currentScene->getChildByIDRecursive("MenuLayer")){
				CCDirector::popScene();
			}
		}
		else{
			currentScene->getChildByIDRecursive("settings-layer"_spr)->removeFromParent();
		}
	}*/

	bool replaceScene(CCScene *pScene){

		if(!GlobalVars::getSharedInstance()->isInitialLaunch){
			return CCDirector::replaceScene(pScene);
		}
		else{
			CCScene* currentScene = CCScene::get();
			CCLayer* child = typeinfo_cast<CCLayer*>(currentScene->getChildren()->objectAtIndex(0));

			LoadingLayer* loadingLayer = typeinfo_cast<LoadingLayer*>(child);
			
			if(loadingLayer){
				MyLoadingLayer* myLoadingLayer = static_cast<MyLoadingLayer*>(child);
				if(myLoadingLayer->m_fields->didHook){
					if(GlobalVars::getSharedInstance()->isInitialLaunch){
						myLoadingLayer->scheduleOnce(schedule_selector(MyLoadingLayer::doFadeOut), 0.05f);
					}
				}
				else{
					GlobalVars::getSharedInstance()->isInitialLaunch = false;
					return CCDirector::replaceScene(pScene);
				}
			}
		}
		return true;
	}
};