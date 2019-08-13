#ifndef _FCONTEXT_H_
#define _FCONTEXT_H_
#include "../QtIncludes.h"
#include "NativeInterface/NativeInterfaceEnums.h"

namespace ParadigmEditor
{
	class RenderWidget : public QDockWidget
	{
		Q_OBJECT
		//Q_DISABLE_COPY(RenderWidget)
		
		public:
			RenderWidget(ETargetViewport _target, const QString& _name, QWidget* _parent = NULL);
			virtual ~RenderWidget() = default;
			virtual QPaintEngine* paintEngine() const { return NULL; }
		

		private:
			virtual void update();
			virtual void resizeEvent(QResizeEvent* _event);
			virtual void paintEvent(QPaintEvent* _event);
			virtual void mousePressEvent(QMouseEvent* _event);
			virtual void mouseReleaseEvent(QMouseEvent* _event);
			virtual void customContextMenuRequested(const QPoint &pos);

		private:
			int m_Width;
			int m_Height;
			ETargetViewport m_TargetViewport;
	};
}

#endif