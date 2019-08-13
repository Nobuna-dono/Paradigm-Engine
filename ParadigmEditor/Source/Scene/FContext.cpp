#include <../ParadigmEditor/Include/ParadigmEditor.h>
#include "Include/Scene/FContext.h"
#include "../Include/QtIncludes.h"
#include "FParadigmEngine.h"

namespace ParadigmEditor
{
	RenderWidget::RenderWidget(ETargetViewport _target, const QString& _name, QWidget* _parent) : QDockWidget(_name, _parent)
	{		
		setAttribute(Qt::WA_PaintOnScreen, true);
		setAttribute(Qt::WA_NativeWindow, true);
		
		this->setContextMenuPolicy(Qt::PreventContextMenu);

		if (!PARADIGM_GRAPHICS->CreateViewport(_target, (uint)size().width(), (uint)size().height(), false, true, (void*)winId()))
			THROW_PARADIGM_EXCEPTION("Failed to create context editor");
		
		PARADIGM_INPUT->CreateInputSystem(_target);
		m_TargetViewport = _target;

		QTimer* tmp = ((FParadigmEditor*)_parent)->Timer;
		connect(tmp, &QTimer::timeout, this, &RenderWidget::update);
	}
	
	void RenderWidget::mousePressEvent(QMouseEvent * _event)
	{
		if (_event->button() == Qt::RightButton || _event->button() == Qt::LeftButton)
		{
			PARADIGM_CONTEXT->SetFocusOn(m_TargetViewport);
		}
	}

	void RenderWidget::mouseReleaseEvent(QMouseEvent * _event)
	{
		Q_UNUSED(_event);
	}

	void RenderWidget::customContextMenuRequested(const QPoint &pos)
	{
		Q_UNUSED(pos);
	}

	void RenderWidget::update()
	{
		paintEvent(nullptr);
	}

	void RenderWidget::resizeEvent(QResizeEvent* _event)
	{
		if (!size().width() || !size().height())
			return;
		PARADIGM_GRAPHICS->ResizeViewport(m_TargetViewport, size().width(), size().height());
	}
	
	void RenderWidget::paintEvent(QPaintEvent* _event)
	{				
		Q_UNUSED(_event);
		PARADIGM.Frame();		
	}

}